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

#include "Translator.h"
#include "TranslationUnit.h"

#include <iostream>

Translator::Translator(DataLayer* il, DataLayer* ol){
	if(il->getDomain() != ol->getDomain()){
		std::cerr << "Domains do not match" << std::endl;
	}
	inputLayer=il;
	outputLayer=ol;
};

Translator::~Translator(){
};

void Translator::registerTU(TranslationUnit* t){
	tu=t;
}

double Translator::getCurrentTime(){
	return tu->getTime();
}

