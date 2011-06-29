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
    \brief This file is a testing binary for the LogBetaFunction class
  */

#include "functions/LogBetaFunction.h"

#include <iostream>

int main(int argc, char** argv) {
  LogBetaFunction<size_t, 2> lB_1;

  Eigen::Matrix<size_t, 2, 1> argument1;

  argument1(0) = 1;
  argument1(1) = 1;
  std::cout << "lB_1(1, 1): " << std::fixed << lB_1(argument1) << std::endl;
  if (fabs(lB_1(argument1) -  0.0) > std::numeric_limits<double>::epsilon())
    return 1;

  argument1(0) = 1;
  argument1(1) = 2;
  std::cout << "lB_1(1, 2): " << std::fixed << lB_1(argument1) << std::endl;
  if (fabs(lB_1(argument1) -  log(0.5)) >
    std::numeric_limits<double>::epsilon())
    return 1;

  argument1(0) = 2;
  argument1(1) = 2;
  std::cout << "lB_1(2, 2): " << lB_1(argument1) << std::endl;
  if (fabs(lB_1(argument1) -  log(1.0 / 6.0)) >
    std::numeric_limits<double>::epsilon())
    return 1;

  LogBetaFunction<double, 2> lB_2;

  Eigen::Matrix<double, 2, 1> argument2;

  argument2(0) = 0.5;
  argument2(1) = 0.5;
  std::cout << "lB_2(0.5, 0.5): " << std::fixed << lB_2(argument2) << std::endl;
  if (fabs(lB_2(argument2) -  log(M_PI)) > 1e-6)
    return 1;
  argument2(0) = 0.4;
  argument2(1) = -0.6;
  std::cout << "lB_2(0.4, -0.6): " << std::fixed << lB_2(argument2)
    << std::endl;

  return 0;
}
