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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file OuterProduct.cpp
    \brief This file is a testing binary for the OuterProduct function.
  */

#include <iostream>

#include "utils/OuterProduct.h"
#include "base/Timestamp.h"

int main (int argc, char** argv) {
  Eigen::Matrix<double, 2, 1> v1(2.0, 4.0);
  Eigen::Matrix<double, 2, 1> v2(3.0, 5.0);
  std::cout << "v1 x v2 (Outer): " << std::endl
    << outerProduct<double, 2, 2>(v1, v2) << std::endl;
  std::cout << "v1 x v1 (Outer): " << std::endl << outerProduct<double, 2>(v1)
    << std::endl;
  std::cout << "v1 x v2 (Eigen): " << std::endl << v1 * v2.transpose()
    << std::endl;
  std::cout << "v1 x v1 (Eigen): " << std::endl << v1 * v1.transpose()
    << std::endl;
  std::cout << "Evaluating performance" << std::endl;
  Eigen::Matrix<double, 2, 2> res;
  double before = Timestamp::now();
  for (size_t i = 0; i < 1000; ++i)
    res = v1 * v2.transpose();
  double after = Timestamp::now();
  std::cout << "v1 x v2 (Eigen): " << (after - before) / 1000 << " [s]"
    << std::endl;
  before = Timestamp::now();
  for (size_t i = 0; i < 1000; ++i)
    res = v1 * v1.transpose();
  after = Timestamp::now();
  std::cout << "v1 x v1 (Eigen): " << (after - before) / 1000 << " [s]"
    << std::endl;
  before = Timestamp::now();
  for (size_t i = 0; i < 1000; ++i)
    res = outerProduct<double, 2, 2>(v1, v2);
  after = Timestamp::now();
  std::cout << "v1 x v2 (Outer): " << (after - before) / 1000 << " [s]"
    << std::endl;
  before = Timestamp::now();
  for (size_t i = 0; i < 1000; ++i)
    res = outerProduct<double, 2>(v1);
  after = Timestamp::now();
  std::cout << "v1 x v1 (Outer): " << (after - before) / 1000 << " [s]"
    << std::endl;
  return 0;
}
