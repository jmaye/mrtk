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

/** \file EstimatorBayesImproper.cpp
    \brief This file is a testing binary for the EstimatorBayesImproper class
  */

#include <iostream>

#include "statistics/EstimatorBayesImproper.h"

int main(int argc, char** argv) {
  NormalDistribution<1> distNorm1(5, 2);
  std::vector<double> samplesNorm1;
  distNorm1.getSamples(samplesNorm1, 1000);
  EstimatorBayesImproper<NormalDistribution<1> > estNorm1;
  estNorm1.addPoints(samplesNorm1.begin(), samplesNorm1.end());
  std::cout << "Estimation1: " << std::endl << estNorm1 << std::endl;
  NormalDistribution<2> distNorm2(Eigen::Matrix<double, 2, 1>(5, 5),
    (Eigen::Matrix<double, 2, 2>() << 2, 1, 1, 2).finished());
  std::vector<Eigen::Matrix<double, 2, 1> > samplesNorm2;
  distNorm2.getSamples(samplesNorm2, 1000);
  EstimatorBayesImproper<NormalDistribution<2> > estNorm2;
  estNorm2.addPoints(samplesNorm2.begin(), samplesNorm2.end());
  std::cout << "Estimation2: " << std::endl << estNorm2 << std::endl;
  LinearRegression<2> distLine(Eigen::Matrix<double, 2, 1>(2.0, 2.0), 2.0);
  std::vector<Eigen::Matrix<double, 2, 1> > samplesLine;
  for (double x = -10; x < 10; x += 0.01) {
    distLine.setBasis((Eigen::Matrix<double, 1, 1>() << x).finished());
    samplesLine.push_back(Eigen::Matrix<double, 2, 1>(distLine.getSample()));
  }
  EstimatorBayesImproper<LinearRegression<2> > estLine;
  estLine.addPoints(samplesLine.begin(), samplesLine.end());
  std::cout << "Estimation3: " << std::endl << estLine << std::endl;
  return 0;
}
