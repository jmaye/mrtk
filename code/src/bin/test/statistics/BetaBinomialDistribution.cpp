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

/** \file BetaBinomialDistribution.cpp
    \brief This file is a testing binary for the BetaBinomialDistribution class
  */

#include <iostream>
#include <limits>

#include "statistics/BetaBinomialDistribution.h"

int main(int argc, char** argv) {
  BetaBinomialDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getAlpha(): " << dist.getAlpha() << std::endl << std::endl;
  std::cout << "dist.getBeta(): " << dist.getBeta() << std::endl << std::endl;

  std::cout << "dist.setAlpha(2.0)" << std::endl << std::endl;
  std::cout << "dist.setBeta(5.0)" << std::endl << std::endl;
  std::cout << "dist.setNumTrials(5)" << std::endl << std::endl;
  const double alpha = 2.0;
  const double beta = 5.0;
  const size_t numTrials = 5;
  dist.setAlpha(alpha);
  dist.setBeta(beta);
  dist.setNumTrials(numTrials);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getAlpha() != alpha)
    return 1;
  if (dist.getBeta() != beta)
    return 1;
  if (dist.getNumTrials() != numTrials)
    return 1;

  std::cout << "dist.getMean(): " << std::fixed << dist.getMean() << std::endl
    << std::endl;
  if (fabs(dist.getMean() - numTrials * alpha / (alpha + beta)) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed << dist.getVariance()
    << std::endl << std::endl;
  if (fabs(dist.getVariance() - numTrials * alpha * beta *
      (alpha + beta + numTrials) / (alpha + beta) / (alpha + beta) /
      (alpha + beta + 1)) > std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.setAlpha(0.0)" << std::endl;
    dist.setAlpha(0.0);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist.setBeta(0.0)" << std::endl;
    dist.setBeta(0.0);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<size_t, 2, 1> > samples;
  dist.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i](0) << std::endl;
  std::cout << std::endl;

  BetaBinomialDistribution distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getAlpha() != dist.getAlpha())
    return 1;
  if (distCopy.getBeta() != dist.getBeta())
    return 1;
  BetaBinomialDistribution distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getAlpha() != dist.getAlpha())
    return 1;
  if (distAssign.getBeta() != dist.getBeta())
    return 1;

  return 0;
}
