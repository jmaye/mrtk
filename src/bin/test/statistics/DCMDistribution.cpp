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

/** \file DCMDistribution.cpp
    \brief This file is a testing binary for the DCMDistribution class
  */

#include <iostream>
#include <limits>

#include "statistics/DCMDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing DCMDistribution<3>" << std::endl << std::endl;
  DCMDistribution<3> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getAlpha(): " << std::endl << dist.getAlpha()
    << std::endl << std::endl;
  std::cout << "dist.getNumTrials(): " << std::endl << dist.getAlpha()
    << std::endl << std::endl;

  std::cout << "dist.setAlpha(2.0, 5.0, 10.0)" << std::endl << std::endl;
  std::cout << "dist.setNumTrials(5)" << std::endl << std::endl;
  const Eigen::Matrix<double, 3, 1> alpha(2.0, 5.0, 10.0);
  const size_t numTrials = 5;
  dist.setAlpha(alpha);
  dist.setNumTrials(numTrials);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getAlpha() != alpha)
    return 1;
  if (dist.getNumTrials() != numTrials)
    return 1;

  std::cout << "dist.getMean(): " << std::endl <<
    dist.getMean() << std::endl << std::endl;
  std::cout << "dist.getCovariance(): " << std::endl <<
    dist.getCovariance() << std::endl << std::endl;

  try {
    std::cout << "dist.setAlpha(0.0, 0.9, 10.9)" << std::endl;
    Eigen::Matrix<double, 3, 1> alphaWrong(0.0, 0.9, 10.9);
    dist.setAlpha(alphaWrong);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 3, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<int, 3, 1> > samples;
  dist.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  DCMDistribution<3> distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getAlpha() != dist.getAlpha())
    return 1;
  DCMDistribution<3> distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getAlpha() != dist.getAlpha())
    return 1;
  std::cout << std::endl;

  return 0;
}
