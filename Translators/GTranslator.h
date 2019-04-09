/*******************************************************************************
 * Copyright (C) 2019 Moritz Gütlein, Chair of Computer Science 7,
 * FAU Erlangen-Nuernberg
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#ifndef GTranslator_H_
#define GTranslator_H_

#include "Translator.h"
#include <math.h>
#include <string>

#define SPEEDNORM 10.0
#define STD 1
#define NUMLANES 1

class GTranslator : public Translator {

public:
	GTranslator(DataLayer* i, DataLayer*o) : Translator(i,o){};
	~GTranslator(){};

	void receive(std::vector<Parameter *> meso){
		std::vector<Parameter *> micro = translate(meso);
		send(micro);

	};

	std::vector<Parameter *> translate(std::vector<Parameter *> meso){
		std::string vehID;
		std::string route;
		double speed;
		std::string lane;

		//extract parameters
		for(Parameter* param : meso){
			if(param->id == "vehID"){
				vehID = ((IParameter<std::string>*)param)->getValue();
			} else if(param->id == "route"){
				route = ((IParameter<std::string>*)param)->getValue();
			}
			free(param);
		}

		//sample a random velocity
		double r1,r2;
		do{
		r1 = ((double) rand() / (RAND_MAX))*2-1;
		r2 = ((double) rand() / (RAND_MAX))*2-1;
		}while(r1*r1+r2*r2 >=1 || r1*r1+r2*r2 <= 0);
		double p = sqrt((-2*log(r1*r1+r2*r2))/(r1*r1+r2*r2));
		speed = STD * r1 * p + SPEEDNORM;


		//sample a random lane
		//todo: NUMLANES for every road segment
		double r3 =  rand() % NUMLANES;
		int l = r3 * (speed/SPEEDNORM);
		if(l >= NUMLANES) lane = NUMLANES-1;
		lane = to_string(l);

		//create micro tuple
		std::vector<Parameter *> micro;
		micro.push_back((Parameter*)(new IParameter<std::string>("vehID", vehID)));
		micro.push_back((Parameter*)(new IParameter<std::string>("route", route)));
		micro.push_back((Parameter*)(new IParameter<std::string>("lane", lane)));
		micro.push_back((Parameter*)(new IParameter<double>("speed", speed)));

		return micro;
	};

	void send(std::vector<Parameter *> micro){
		tu->send(outputLayer, micro);
	};

	void loop(){};
};
#endif
