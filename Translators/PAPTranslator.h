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

#ifndef PAPTranslator_H_
#define PAPTranslator_H_

#include <math.h>
#include <map>
#include "../Translator.h"

#define FIXEDROUTE "f g h a"

class PAPTranslator;
void work(PAPTranslator* t);

class PAPTranslator : public Translator {
private:
	int TIMESTEP = 1000; //in ms
	int spawnCount = 0;

public:
	//quick and dirty
	std::map<std::string, double> arrivalRates;
	std::map<double, std::string> arrivals;
	std::map<std::string, double> arrivalsByRoad;
	std::map<std::string, double> scheduleTimesByRoad;

	PAPTranslator(DataLayer* i, DataLayer*o) : Translator(i,o){};
	~PAPTranslator(){};


	void scheduleArrival(string arrivalRoad){
		double t = getCurrentTime();
		double nextArrivalTime = t + calcInterArrival(arrivalRoad);

		arrivals[nextArrivalTime] = arrivalRoad;
		arrivalsByRoad[arrivalRoad] = nextArrivalTime;
		scheduleTimesByRoad[arrivalRoad] = t;
	};

	double calcInterArrival(string arrivalRoad){
		double r = ((double) rand() / (RAND_MAX));
		double nextArrivalTime =  - log(r)/arrivalRates[arrivalRoad];
		return nextArrivalTime;
	};

	void receive(std::vector<Parameter *> macro){
		double t = getCurrentTime();
		std::string roadID;
		double volume;

		for(Parameter* param : macro){
			if(param->id == "roadID"){
				roadID = ((IParameter<std::string>*)param)->getValue();
			} else if(param->id == "volume"){
				volume = ((IParameter<double>*)param)->getValue();
			}
			free(param);
		}

		arrivalRates[roadID] = volume;

		//check if there is already an arrival, if not: easy
		if(arrivalsByRoad[roadID] ==0){
			scheduleArrival(roadID);
		}
		//if so, interpolate between old an new arrival and delete old
		else{
			double Ts = scheduleTimesByRoad[roadID];
			double newIA = calcInterArrival(roadID);
			double oldIA = arrivalsByRoad[roadID]-Ts;
			double R = (t-Ts)/(t-Ts+newIA);
			double intIA = R * oldIA + (1-R) * newIA;

			//todo: problem for multiple roads, if arrival is scheduled for exactly same time
			arrivals.erase(arrivalsByRoad[roadID]);

			arrivalsByRoad[roadID]=Ts+intIA;
			scheduleTimesByRoad[roadID]=Ts;
			arrivals[Ts+intIA] = roadID;
		}
	};

	void send(std::vector<Parameter *> meso){
		tu->send(outputLayer, meso);

		for(Parameter* param : meso){
			free(param);
		}
	};


	void loop(){
		if(arrivals.size()<1) return;
		double t = getCurrentTime();

		//get time and road of next arrival
		double arrivalTime = arrivals.begin()->first;
		std::string arrivalRoad = arrivals.begin()->second;
		if(t < arrivalTime)	return;

		std::string route = FIXEDROUTE; //todo: sample route from map
		std::string vehID = "papCar" + (spawnCount++);

		arrivals.erase(arrivals.begin());
		std::vector<Parameter *> meso;
		meso.push_back((Parameter*)(new IParameter<std::string>("vehID", vehID)));
		meso.push_back((Parameter*)(new IParameter<std::string>("route", route)));
		send(meso);

		//recalc next arrivalTime for arrivalRoad
		scheduleArrival(arrivalRoad);
	};
};

#endif
