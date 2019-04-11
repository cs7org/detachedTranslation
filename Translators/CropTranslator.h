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

#ifndef CropTranslator_H_
#define CropTranslator_H_

#include "../Translator.h"

class CropTranslator : public Translator {

public:
	CropTranslator(DataLayer* i, DataLayer*o) : Translator(i,o){};
	~CropTranslator(){};
	void receive(std::vector<Parameter *> micro){

		std::vector<Parameter *> meso = translate(micro);
		send(meso);
	};

	std::vector<Parameter *> translate(std::vector<Parameter *> micro){

		std::vector<Parameter *> meso;

		for(Parameter* param : micro){
			if(param->getID() == "vehID"){
				meso.push_back(param);
			} else if (param->getID() == "route"){
				meso.push_back(param);
			}
		}

		//todo: error checks
		return meso;
	};

	void send(std::vector<Parameter *> v){
		tu->send(outputLayer, v);
	};

	void loop(){};
};
#endif
