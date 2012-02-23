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

/** \file Factory.cpp
    \brief This file is a testing binary for the Factory class
  */

#include <iostream>

#include "base/Factory.h"

int main(int argc, char** argv) {
  Factory<size_t, size_t>& factory = Factory<size_t, size_t>::getInstance();
  std::cout << "Number of types: " << factory.getNumTypes() << std::endl;
  size_t type = 1;
  std::cout << "Inserting an object in the factory" << std::endl;
  factory.registerType(&type, 0);
  std::cout << "Number of types: " << factory.getNumTypes() << std::endl;
  std::cout << "Factory content: " << std::endl
    << factory;
  return 0;
}
