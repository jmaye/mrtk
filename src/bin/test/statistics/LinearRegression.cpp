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
  std::cout << "l.setBasis(2.0)" << std::endl;
  linearRegression.setLinearBasisFunction(LinearBasisFunction<double, 2>(
    Eigen::Matrix<double, 2, 1>(2.0, 2.0)));
  linearRegression.setVariance(2.0);
  linearRegression.setBasis((Eigen::Matrix<double, 1, 1>() << 2.0).finished());
  if (linearRegression.getLinearBasisFunction().getCoefficients() !=
    Eigen::Matrix<double, 2, 1>(2.0, 2.0))
    return 1;
  if (linearRegression.getVariance() != 2.0)
    return 1;
  if (linearRegression.getBasis() !=
      (Eigen::Matrix<double, 1, 1>() << 2.0).finished())
    return 1;
  std::cout << "New parameters: " << std::endl << linearRegression
    << std::endl;
  std::cout << "l.getValue(2): " << linearRegression(
    Eigen::Matrix<double, 2, 1>(2, 6)) << std::endl;
  std::cout << "l.getSample(): " << std::endl << linearRegression.getSample()
    << std::endl;
  std::cout << "l.getMean(): " << linearRegression.getMean() << std::endl;

  LinearRegression<2> linCopy(linearRegression);
  std::cout << "Copy constructor: " << std::endl << linCopy << std::endl
    << std::endl;
  if (linCopy.getLinearBasisFunction().getCoefficients() !=
      linearRegression.getLinearBasisFunction().getCoefficients())
    return 1;
  if (linCopy.getVariance() != linearRegression.getVariance())
    return 1;
  LinearRegression<2> linAssign = linearRegression;
  std::cout << "Assignment operator: " << std::endl << linAssign << std::endl;
  if (linAssign.getLinearBasisFunction().getCoefficients() !=
      linearRegression.getLinearBasisFunction().getCoefficients())
    return 1;
  if (linAssign.getVariance() != linearRegression.getVariance())
    return 1;

  return 0;
}