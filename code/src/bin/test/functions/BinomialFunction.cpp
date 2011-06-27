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

/** \file BinomialFunction.cpp
    \brief This file is a testing binary for the BinomialFunction class
  */

#include "functions/BinomialFunction.h"

#include <iostream>

int main(int argc, char** argv) {
  BinomialFunction b;

  Eigen::Matrix<size_t, 2, 1> argument1;

  argument1(0) = 1;
  argument1(1) = 1;
  std::cout << "b(1, 1): " << b(argument1) << std::endl;
  argument1(0) = 1;
  argument1(1) = 2;
  std::cout << "b(1, 2): " << b(argument1) << std::endl;
  argument1(0) = 2;
  argument1(1) = 2;
  std::cout << "b(2, 2): " << b(argument1) << std::endl;

  return 0;
}
