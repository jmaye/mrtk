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

/** \file GammaFunction.cpp
    \brief This file is a testing binary for the GammaFunction class
  */

#include "functions/GammaFunction.h"
#include "functions/FactorialFunction.h"

#include <iostream>
#include <limits>

int main(int argc, char** argv) {
  GammaFunction<size_t> G_1;

  std::cout << "G_1(1): " << G_1(1) << std::endl;
  if (G_1(1) != 1)
    return 1;

  std::cout << "G_1(2): " << G_1(2) << std::endl;
  if (G_1(2) != 1)
    return 1;

  try {
    std::cout << "G_1(0): " << G_1(0) << std::endl;
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }

  FactorialFunction f;
  if (G_1(10) != f(9))
    return 1;

  GammaFunction<double> G_2;

  std::cout << "G_2(0.5): " << G_2(0.5) << std::endl;
  if (fabs(G_2(0.5) - sqrt(M_PI)) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "G_2(1.0): " << G_2(1.0) << std::endl;
  if (fabs(G_2(1.0) - 1.0) > std::numeric_limits<double>::epsilon())
    return 1;

  return 0;
}
