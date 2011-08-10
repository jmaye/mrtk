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

#include "statistics/LinearRegression.h"

int main(int argc, char** argv) {
  LinearRegression<2> linearRegression;
  std::cout << "Default parameters: " << std::endl << linearRegression
    << std::endl;
  std::cout << "l.getCoefficients(): " << std::endl <<
    linearRegression.getCoefficients() << std::endl;
  std::cout << "l.setVariance(2)" << std::endl;
  linearRegression.setVariance(2);
  std::cout << "l.setCoefficients(2, 2)" << std::endl;
  linearRegression.setCoefficients(Eigen::Matrix<double, 2, 1>(2, 2));
  std::cout << "New parameters: " << std::endl << linearRegression
    << std::endl;
  std::cout << "l.getValue(2):" << linearRegression(2) << std::endl;
  return 0;
}
