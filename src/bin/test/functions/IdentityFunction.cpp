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

/** \file IdentityFunction.cpp
    \brief This file is a testing binary for the IdentityFunction class
  */

#include <iostream>

#include <Eigen/Core>
#include <Eigen/Array>

#include "functions/IdentityFunction.h"

int main(int argc, char** argv) {
  IdentityFunction<double> i1;
  std::cout << "i(2.0) = " << i1(2.0) << std::endl;
  if (i1(2.0) != 2.0)
    return 1;
  IdentityFunction<size_t> i2;
  std::cout << "i(3) = " << i2(3) << std::endl;
  if (i2(3) != 3)
    return 1;
  IdentityFunction<Eigen::Matrix<double, 2, 2> > i3;
  std::cout << "i([-2 0; 0 -2]) = " << std::endl <<
    i3((Eigen::Matrix<double, 2, 2>() << -2, 0, 0, -2).finished()) << std::endl;
  if (i3((Eigen::Matrix<double, 2, 2>() << -2, 0, 0, -2).finished()) !=
    (Eigen::Matrix<double, 2, 2>() << -2, 0, 0, -2).finished())
    return 1;
  return 0;
}
