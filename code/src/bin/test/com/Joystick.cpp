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

/** \file Joystick.cpp
    \brief This file is a testing binary for the Joystick class
  */

#include <iostream>

#include "com/Joystick.h"
#include "exceptions/SystemException.h"

int main(int argc, char** argv) {
  Joystick joystick;
  try {
    std::cout << "Driver version: " << joystick.getDriverVersion() << std::endl;
    std::cout << "Identifier string: " << joystick.getIdentifierString()
      << std::endl;
    for (size_t i = 0; i < 10; ++i)
      std::cout << "Joystick state: " << std::endl << joystick.getState()
        << std::endl;
  }
  catch (SystemException& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
