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

#include "MvDiscreteFunction.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MvDiscreteFunction::MvDiscreteFunction() {
}

MvDiscreteFunction::MvDiscreteFunction(const MvDiscreteFunction& other) {
}

MvDiscreteFunction& MvDiscreteFunction::operator = (const MvDiscreteFunction& other) {
  return *this;
}

MvDiscreteFunction::~MvDiscreteFunction() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void MvDiscreteFunction::read(std::istream& stream) {
}

void MvDiscreteFunction::write(std::ostream& stream) const {
}

void MvDiscreteFunction::read(std::ifstream& stream) {
}

void MvDiscreteFunction::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const MvDiscreteFunction& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, MvDiscreteFunction& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const MvDiscreteFunction& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, MvDiscreteFunction& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

