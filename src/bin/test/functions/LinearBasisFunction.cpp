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

/** \file LinearBasisFunction.cpp
    \brief This file is a testing binary for the LinearBasisFunction class
  */

#include <iostream>

#include "functions/LinearBasisFunction.h"

int main(int argc, char** argv) {
  LinearBasisFunction<double, 2> lbf(Eigen::Matrix<double, 2, 1>(2.0, 1.0));
  std::cout << "lbf(2.0) = " << lbf(2.0) << std::endl;
  if (lbf(2.0) != 4)
    return 1;
  std::cout << "lbf(3.0) = " << lbf(3.0) << std::endl;
  if (lbf(3.0) != 5)
    return 1;
  std::cout << "lbf.getCoefficients(): " << std::endl << lbf.getCoefficients()
    << std::endl;
  std::cout << "lbf.setCoefficients((1.0, 2.0))"
    << std::endl;
  lbf.setCoefficients(Eigen::Matrix<double, 2, 1>(1.0, 2.0));
  std::cout << "lbf.getCoefficients(): " << std::endl << lbf.getCoefficients()
    << std::endl;
  std::cout << "lbf(2.0) = " << lbf(2.0) << std::endl;
  if (lbf(2.0) != 5)
    return 1;
  std::cout << "lbf(3.0) = " << lbf(3.0) << std::endl;
  if (lbf(3.0) != 7)
    return 1;
  LinearBasisFunction<double, 3>
    lbf3(Eigen::Matrix<double, 3, 1>(2.0, 1.0, 6.0));
  std::cout << "lbf3(2.0, 2.0) = " <<
    lbf3(Eigen::Matrix<double, 2, 1>(2.0, 2.0)) << std::endl;
  if (lbf3(Eigen::Matrix<double, 2, 1>(2.0, 2.0)) != 16)
    return 1;
  std::cout << "lbf3(3.0, 1.0) = " <<
    lbf3(Eigen::Matrix<double, 2, 1>(3.0, 1.0)) << std::endl;
  if (lbf3(Eigen::Matrix<double, 2, 1>(3.0, 1.0)) != 11)
    return 1;
  return 0;
}
