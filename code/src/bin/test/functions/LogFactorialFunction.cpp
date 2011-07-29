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

/** \file LogFactorialFunction.cpp
    \brief This file is a testing binary for the LogFactorialFunction class
  */

#include "functions/LogFactorialFunction.h"
#include "functions/FactorialFunction.h"

#include <limits>
#include <iostream>

int main(int argc, char** argv) {
  LogFactorialFunction lf;
  FactorialFunction f;

  std::cout << "lf(0): " << std::fixed << lf(0) << std::endl;
  if (fabs(lf(0) - 0.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "lf(1): " << std::fixed << lf(1) << std::endl;
  if (fabs(lf(1) - 0.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "lf(2): " << std::fixed << lf(2) << std::endl;
  if (fabs(lf(2) - log(f(2))) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "lf(3): " << std::fixed << lf(3) << std::endl;
  if (fabs(lf(3) - log(f(3))) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "lf(4): " << std::fixed << lf(4) << std::endl;
  if (fabs(lf(4) - log(f(4))) > 1e-12)
    return 1;

  std::cout << "lf(5): " << std::fixed << lf(5) << std::endl;
  if (fabs(lf(5) - log(f(5))) > 1e-12)
    return 1;

  return 0;
}
