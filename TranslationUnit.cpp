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

#include "TranslationUnit.h"

TranslationUnit::TranslationUnit(Translator* a, Translator* d){
	if(a->getInputLayer()->getID() != d->getOutputLayer()->getID() ||
			a->getOutputLayer()->getID() != d->getInputLayer()->getID() ||
			a->getOutputLayer()->getDomain() != d->getInputLayer()->getDomain() )	{
		std::cerr << "Translators' data layers do not match" << std::endl;
	}
	ta=a;
	td=d;
	ta->registerTU(this);
	td->registerTU(this);
	aggregationLayer = ta->getOutputLayer();
	disaggregationLayer = ta->getInputLayer();
}

TranslationUnit::~TranslationUnit(){
	free(federate);
}

void TranslationUnit::init(std::string federationN, std::string federateN){
	federationName = federationN;
	federateName = federateN;
	federate = new TranslatorFederate(this);
	federate->init(federationN, federateN);
}

void TranslationUnit::send(DataLayer* layer, std::vector<Parameter*> data){
	std::cout << "TranslationUnit: Send data in: " << layer->getDomain() << " " << layer->getID() << std::endl;
	printParameterSet(data);
	federate->sendInteraction(layer, data);
}

void TranslationUnit::addRespLink(std::vector<std::string> links) {
	federate->addRespLinks(links);
}

void TranslationUnit::receive(DataLayer* layer, std::vector<Parameter*> data){
	std::cout << "TranslationUnit: Receive data in " << layer->getID() << std::endl;
	Translator* resp;
	if(ta->getInputLayer()->getID() == layer->getID()){
		ta->receive(data);
	} else if(td->getInputLayer()->getID() == layer->getID()){
		td->receive(data);
	}
	else{
		std::cerr << "received data from unkown layer: " << layer->getID() << std::endl;
		return;
	}
}

void TranslationUnit::timeAdvance(double d){
	federate->advanceTime(d);
}

int TranslationUnit::getTime(){
	return federate->curTime;
}

void TranslationUnit::printParameterSet(std::vector<Parameter*> data){
	for(Parameter* param : data){
		std::cout << param->getID() << " ";
		if(param->getType() == typeid(int).name()){
			std::cout << ((IParameter<int>*)param)->getValue() << std::endl;
		} else if(param->getType() == typeid(double).name()){
			std::cout << ((IParameter<double>*)param)->getValue() << std::endl;
		} else if(param->getType() == typeid(std::string).name()){
			std::cout << ((IParameter<std::string>*)param)->getValue() << std::endl;
		}
	}
}
