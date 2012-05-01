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

/** \file BayesianLinearRegression.cpp
    \brief This file is a testing binary for Bayesian linear regression
  */

#include <iostream>

#include "statistics/LinearRegression.h"
#include "statistics/EstimatorBayesImproper.h"
#include "base/Timestamp.h"

int main(int argc, char** argv) {
  LinearRegression<2> distLine(Eigen::Matrix<double, 2, 1>(2.0, 2.0), 2.0);
  std::vector<Eigen::Matrix<double, 2, 1> > samplesLine;
  for (double x = -10; x < 10; x += 0.01) {
    distLine.setBasis((Eigen::Matrix<double, 1, 1>() << x).finished());
    samplesLine.push_back(Eigen::Matrix<double, 2, 1>(distLine.getSample()));
  }
  double before = Timestamp::now();
  EstimatorBayesImproper<LinearRegression<2> > estLine;
  estLine.addPoints(samplesLine.begin(), samplesLine.end());
  double after = Timestamp::now();
  std::cout << "Estimation1: " << std::endl << estLine << std::endl;
  std::cout << "Time: " << after - before << " [s]" << std::endl;

  return 0;
}
