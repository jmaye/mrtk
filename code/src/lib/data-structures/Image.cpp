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

#include "data-structures/Image.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Image::Image() {
}

Image::Image(const Image& other) {
}

Image& Image::operator = (const Image& other) {
  return *this;
}

Image::~Image() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Image::read(std::istream& stream) {
}

void Image::write(std::ostream& stream) const {
}

void Image::read(std::ifstream& stream) {
}

void Image::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const Image& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, Image& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const Image& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, Image& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

