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

#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_

#include <iostream>
#include <vector>
#include <unistd.h>
#include <iostream>

#include "DataLayer.h"
#include "Parameter.h"
#include "TranslationUnit.h"

class TranslationUnit;

/*******************************************************************************
 * Base class for implementing concrete translators. Translator receives() and
 * processes incoming data. Depending on purpose, data may be directly forwarded
 * via send(). Another option is to use loop() and continuously calculate if
 * something should be send().
 ******************************************************************************/

class Translator {
protected:
	int TIMESTEP = 1000; //in ms
	volatile bool running = true;
	DataLayer* inputLayer;
	DataLayer* outputLayer;
	TranslationUnit* tu;

public:
	void registerTU(TranslationUnit* t);
	double getCurrentTime();
	double getTimeStep(){return TIMESTEP;}

	Translator(DataLayer* il, DataLayer* ol);
	~Translator(){};

	inline DataLayer* getInputLayer(){ return inputLayer;};
	inline DataLayer* getOutputLayer(){ return outputLayer;};

	void start(){
		while(running)loop();
	}

	virtual void receive(std::vector<Parameter *> v){};
	virtual void send(std::vector<Parameter *> v){};
	virtual void loop(){};
};
#endif
