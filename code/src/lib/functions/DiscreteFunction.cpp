/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "DiscreteFunction.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

DiscreteFunction::DiscreteFunction() {
}

DiscreteFunction::DiscreteFunction(const DiscreteFunction& other) {
}

DiscreteFunction& DiscreteFunction::operator = (const DiscreteFunction& other) {
  return *this;
}

DiscreteFunction::~DiscreteFunction() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void DiscreteFunction::read(std::istream& stream) {
}

void DiscreteFunction::write(std::ostream& stream) const {
}

void DiscreteFunction::read(std::ifstream& stream) {
}

void DiscreteFunction::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const DiscreteFunction& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, DiscreteFunction& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const DiscreteFunction& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, DiscreteFunction& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

