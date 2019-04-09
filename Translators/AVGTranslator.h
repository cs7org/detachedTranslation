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

#ifndef AVGTranslator_H_
#define AVGTranslator_H_

#include "Translator.h"
#include <math.h>
#include <map>

class AVGTranslator : public Translator {

private:
	std::map<std::string, short> arrivals;
	std::map<std::string, double> volumes;

public:
	AVGTranslator(DataLayer* i, DataLayer*o) : Translator(i,o){
		TIMESTEP = 30 * 1000;
	};
	~AVGTranslator(){};

	void receive(std::vector<Parameter *> data){
		std::string vehID;
		std::string route;
		std::string road ="";

		for(Parameter* param : data){
			if(param->id == "vehID"){
				vehID = ((IParameter<std::string>*)param)->getValue();
			} else if(param->id == "route"){
				route = ((IParameter<std::string>*)param)->getValue();
			}
			free(param);
		}

		std::size_t pos = route.find(" ");
		if (pos!=std::string::npos){
			road = route.substr(0,pos);
		}
		else{
			road = route; //todo
		}
		arrivals[road]++; //creates new pair if not present
	};

	void send(std::vector<Parameter *> macro){
		tu->send(outputLayer, macro);
		for(Parameter* param : macro){
			free(param);
		}
	};

	void loop(){
		for (auto const& x : arrivals)
		{
		    double vol = x.second/((double)TIMESTEP/1000.0);
		    //did something change?
		    if(vol != volumes[x.first]){
		    	volumes[x.first] = vol;
		    	std::vector<Parameter *> macro;
		    	macro.push_back((Parameter*)(new IParameter<std::string>("roadID", x.first)));
		    	macro.push_back((Parameter*)(new IParameter<double>("volume", vol)));
		    	send(macro);
		    }
		}
		arrivals.clear();
	};
};
#endif
