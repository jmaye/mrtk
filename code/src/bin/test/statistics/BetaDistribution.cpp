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

/** \file BetaDistribution.cpp
    \brief This file is a testing binary for the BetaDistribution class
  */

#include "statistics/BetaDistribution.h"

int main(int argc, char** argv) {
  double f64Alpha = 0.1;
  double f64Beta = 0.9;
  BetaDistribution dist(f64Alpha, f64Beta);
  std::cout << dist << std::endl;

  Eigen::Matrix<double, 2, 1> value;
  value(0) = 0.9;
  value(1) = 0.1;
  std::cout << "pdf(0.9, 0.1): " << std::fixed << dist(value) << std::endl;
  value(0) = 0.1;
  value(1) = 0.9;
  std::cout << "pdf(0.1, 0.9): " << std::fixed << dist(value) << std::endl;

//  try {
//    alpha(0) = 0.0;
//    alpha(1) = 0.9;
//    dist.setAlpha(alpha);
//  }
//  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
//    std::cout << e.what() << std::endl;
//  }

//  try {
//    value(0) = 0.8;
//    value(1) = 0.1;
//    std::cout << "pdf(0.8, 0.1): " << std::fixed << dist(value) << std::endl;
//  }
//  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
//    std::cout << e.what() << std::endl;
//  }

//  try {
//    value(0) = 1.2;
//    value(1) = -0.2;
//    std::cout << "pdf(1.2, -0.2): " << std::fixed << dist(value) << std::endl;
//  }
//  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
//    std::cout << e.what() << std::endl;
//  }

  return 0;
}
