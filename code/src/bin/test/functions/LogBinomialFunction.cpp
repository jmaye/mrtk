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

/** \file LogBinomialFunction.cpp
    \brief This file is a testing binary for the LogBinomialFunction class
  */

#include "functions/LogBinomialFunction.h"

#include <iostream>
#include <limits>

int main(int argc, char** argv) {
  LogBinomialFunction b;

  Eigen::Matrix<size_t, 2, 1> argument;

  argument(0) = 10;
  argument(1) = 0;
  std::cout << "b(10, 0): " << b(argument) << std::endl;
  if (fabs(b(argument) - 0.0) > std::numeric_limits<double>::epsilon())
    return 1;
  argument(0) = 10;
  argument(1) = 1;
  std::cout << "b(10, 1): " << b(argument) << std::endl;
  if (fabs(b(argument) - log(10)) > 1e-10)
    return 1;
  argument(0) = 8;
  argument(1) = 4;
  std::cout << "b(8, 4): " << b(argument) << std::endl;
  if (fabs(b(argument) - log(70)) > 1e-10)
    return 1;

  try {
    argument(0) = 2;
    argument(1) = 5;
    std::cout << "b(2, 5): " << std::fixed << b(argument) << std::endl;
  }
  catch (BadArgumentException<Eigen::Matrix<size_t, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
