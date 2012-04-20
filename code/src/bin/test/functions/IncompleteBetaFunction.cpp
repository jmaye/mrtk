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

/** \file IncompleteBetaFunction.cpp
    \brief This file is a testing binary for the IncompleteBetaFunction class
  */

#include <iostream>

#include "functions/IncompleteBetaFunction.h"

int main(int argc, char** argv) {
  IncompleteBetaFunction<double> f(1.0, 1.0);
  std::cout << "Function parameters: " << std::endl << f << std::endl;
  std::cout << "f.getAlpha(): " << f.getAlpha() << std::endl;
  std::cout << "f.getBeta(): " << f.getBeta() << std::endl;
  std::cout << "f(1): " << f(1) << std::endl;
  std::cout << "f(0.5): " << f(0.5) << std::endl;

  return 0;
}
