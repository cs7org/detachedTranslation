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

#ifndef TRANSLATIONUNIT_H_
#define TRANSLATIONUNIT_H_

#include <string>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>

#include "DataLayer.h"
#include "Parameter.h"
#include "Translator.h"
#include "TranslatorFederate.h"

class TranslatorFederate;
class Translator;

/*******************************************************************************
 * TranslationUnit class holds pointers to the (dis)aggregation translators.
 * It delegates data coming from HLA federate component to the translators
 * and vice versa. Offers timing interface between translators and federates.
 ******************************************************************************/

class TranslationUnit {
private:
	//model
	Translator* ta;
	Translator* td;
	DataLayer* aggregationLayer;
	DataLayer* disaggregationLayer;

	//connection
	std::string federationName;
	std::string federateName;
	TranslatorFederate* federate = 0;

public:

	TranslationUnit(Translator* a, Translator* d);
	~TranslationUnit();

	//prepare
	void init(std::string federationName, std::string federateName);
	void addRespLink(std::vector<std::string> links);

	//run
	void timeAdvance(double t);
	int getTime();
	void send(DataLayer* layer, std::vector<Parameter*>);
	void receive(DataLayer* layer, std::vector<Parameter*>);

	//utils
	void printParameterSet(std::vector<Parameter*> data);
};
#endif
