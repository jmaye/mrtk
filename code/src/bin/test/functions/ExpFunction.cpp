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
    \brief This file is a testing binary for the ExpFunction class
  */

#include "functions/ExpFunction.h"

#include <iostream>

int main(int argc, char** argv) {
  ExpFunction<double> e_1;

  std::cout << "e_1(0): " << e_1(0) << std::endl;
  std::cout << "e_1(-10): " << e_1(-10) << std::endl;
  std::cout << "e_1(1): " << e_1(1) << std::endl;

  ExpFunction<size_t> e_2;

  std::cout << "e_2(0): " << e_2(0) << std::endl;
  std::cout << "e_2(-10): " << e_2(-10) << std::endl;
  std::cout << "e_2(1): " << e_2(1) << std::endl;

  return 0;
}
