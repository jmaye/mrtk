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

/** \file LogGammaFunction.cpp
    \brief This file is a testing binary for the LogGammaFunction class
  */

#include <iostream>
#include <limits>

#include "functions/LogGammaFunction.h"

int main(int argc, char** argv) {
  LogGammaFunction<size_t> lG_1;

  std::cout << "lG_1(1): " << lG_1(1) << std::endl;
  if (fabs(lG_1(1) - 0.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "lG_1(2): " << lG_1(2) << std::endl;
  if (fabs(lG_1(2) - 0.0) > std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "lG_1(0): " << lG_1(0) << std::endl;
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }

  LogFactorialFunction f;
  if (lG_1(10) != f(9))
    return 1;

  LogGammaFunction<double> lG_2;

  std::cout << "lG_2(0.5): " << lG_2(0.5) << std::endl;
  if (fabs(lG_2(0.5) - log(sqrt(M_PI))) >
    std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "lG_2(1.0): " << lG_2(1.0) << std::endl;
  if (fabs(lG_2(1.0) - 0.0) > std::numeric_limits<double>::epsilon())
    return 1;

  return 0;
}
