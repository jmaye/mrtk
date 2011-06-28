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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file BetaFunction.cpp
    \brief This file is a testing binary for the FactorialFunction class
  */

#include "functions/FactorialFunction.h"

#include <iostream>

int main(int argc, char** argv) {
  FactorialFunction f;

  std::cout << "f(0): " << f(0) << std::endl;
  if (f(0) != 1)
    return 1;

  std::cout << "f(1): " << f(1) << std::endl;
  if (f(1) != 1)
    return 1;

  std::cout << "f(2): " << f(2) << std::endl;
  if (f(2) != 2)
    return 1;

  std::cout << "f(3): " << f(3) << std::endl;
  if (f(3) != 6)
    return 1;

  std::cout << "f(4): " << f(4) << std::endl;
  if (f(4) != 24)
    return 1;

  std::cout << "f(5): " << f(5) << std::endl;
  if (f(5) != 120)
    return 1;

  return 0;
}
