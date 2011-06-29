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
    \brief This file is a testing binary for the BetaFunction class
  */

#include "functions/BetaFunction.h"

#include <iostream>
#include <limits>

int main(int argc, char** argv) {
  BetaFunction<size_t, 2> B_1;

  Eigen::Matrix<size_t, 2, 1> argument1;

  argument1(0) = 1;
  argument1(1) = 1;
  std::cout << "B_1(1, 1): " << std::fixed << B_1(argument1) << std::endl;
  if (fabs(B_1(argument1) -  1.0) > std::numeric_limits<double>::epsilon())
    return 1;

  argument1(0) = 1;
  argument1(1) = 2;
  std::cout << "B_1(1, 2): " << std::fixed << B_1(argument1) << std::endl;
  if (fabs(B_1(argument1) -  0.5) > std::numeric_limits<double>::epsilon())
    return 1;

  argument1(0) = 2;
  argument1(1) = 2;
  std::cout << "b_1(2, 2): " << B_1(argument1) << std::endl;
  if (fabs(B_1(argument1) -  1.0 / 6.0) >
    std::numeric_limits<double>::epsilon())
    return 1;

  BetaFunction<double, 2> B_2;

  Eigen::Matrix<double, 2, 1> argument2;

  argument2(0) = 0.5;
  argument2(1) = 0.5;
  std::cout << "B_2(0.5, 0.5): " << std::fixed << B_2(argument2) << std::endl;
  if (fabs(B_2(argument2) -  M_PI) > 1e-6)
    return 1;
  argument2(0) = 0.4;
  argument2(1) = -0.6;
  std::cout << "B_2(0.4, -0.6): " << std::fixed << B_2(argument2) << std::endl;
  if (fabs(B_2(argument2) - 1.4087) > 1e-4)
    return 1;

  return 0;
}
