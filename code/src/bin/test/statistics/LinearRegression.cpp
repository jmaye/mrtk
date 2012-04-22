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

/** \file LinearRegression.cpp
    \brief This file is a testing binary for the LinearRegression class
  */

#include <iostream>

#include <Eigen/Array>

#include "statistics/LinearRegression.h"

int main(int argc, char** argv) {
  LinearRegression<2> linearRegression;
  std::cout << "Default parameters: " << std::endl << linearRegression
    << std::endl;
  std::cout << "l.getLinearBasisFunction(): " << std::endl <<
    linearRegression.getLinearBasisFunction() << std::endl;
  std::cout << "l.getVariance(): " << linearRegression.getVariance()
    << std::endl;
  std::cout <<  "l.setLinearBasisFunction(2.0, 2.0)" << std::endl;
  std::cout << "l.setVariance(2.0)" << std::endl;
  linearRegression.setLinearBasisFunction(LinearBasisFunction<double, 2>(
    Eigen::Matrix<double, 2, 1>(2.0, 2.0)));
  linearRegression.setVariance(2.0);
  if (linearRegression.getLinearBasisFunction().getCoefficients() !=
    Eigen::Matrix<double, 2, 1>(2.0, 2.0))
    return 1;
  if (linearRegression.getVariance() != 2.0)
    return 1;
  std::cout << "New parameters: " << std::endl << linearRegression
    << std::endl;
  std::cout << "l.getValue(2): " << linearRegression(
    Eigen::Matrix<double, 2, 1>(2, 6)) << std::endl;
  return 0;
}
