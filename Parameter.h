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

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <string>
#include <typeinfo>

/*******************************************************************************
 * Parameter container
 ******************************************************************************/

class Parameter {
protected:
	std::string id;
	std::string type;

public:
	std::string getID(){return id;}
	std::string getType(){return type;}
};

template <class T>
class IParameter : public Parameter{
	T value;

public:
	IParameter(std::string i,T v){
		value = v;
		id = i;
		type = typeid(T).name();
	};

	T getValue(){
		return value;
	};
};

#endif
