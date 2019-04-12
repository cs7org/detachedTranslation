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

#ifndef DATALAYER_H_
#define DATALAYER_H_

#include <string>
#include <vector>
#include "Parameter.h"

/*******************************************************************************
 * Generic data layer representation
 ******************************************************************************/

class DataLayer {
private:
	std::string domain;
	std::string id;
	std::vector<Parameter*> interface;

public:
	DataLayer(std::string d, std::string i){
		domain=d;
		id=i;
	};

	void pushParameterType(Parameter* p){
		interface.push_back(p);
	}
	std::string getDomain(){
		return domain;
	}

	std::string getID(){
		return id;
	}
};

#endif /*DATALAYER_H_*/
