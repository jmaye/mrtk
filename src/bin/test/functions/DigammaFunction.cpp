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

/** \file DigammaFunction.cpp
    \brief This file is a testing binary for the DigammaFunction class
  */

#include <iostream>

#include "functions/DigammaFunction.h"

int main(int argc, char** argv) {
  DigammaFunction<size_t> G_1;
  std::cout << "G_1(1): " << G_1(1) << std::endl;
  std::cout << "G_1(2): " << G_1(2) << std::endl;

  DigammaFunction<double> G_2;
  std::cout << "G_2(0.5): " << G_2(0.5) << std::endl;
  std::cout << "G_2(1.0): " << G_2(1.0) << std::endl;

  return 0;
}
