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

/** \file CategoricalDistribution.cpp
    \brief This file is a testing binary for the CategoricalDistribution class
  */

#include <iostream>
#include <limits>

#include "statistics/CategoricalDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing CategoricalDistribution<2>" << std::endl << std::endl;
  CategoricalDistribution<2> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "dist.getProbabilities(): " << std::endl
    << dist.getProbabilities() << std::endl << std::endl;
  std::cout << "dist.getProbability(0): "
    << dist.getProbability(0) << std::endl << std::endl;
  std::cout << "dist.getProbability(1): "
    << dist.getProbability(1) << std::endl << std::endl;

  std::cout << "dist.setProbabilities(0.7, 0.3)" << std::endl << std::endl;
  dist.setProbabilities(Eigen::Matrix<double, 2, 1>(0.7, 0.3));
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  if (dist.getProbabilities() != Eigen::Matrix<double, 2, 1>(0.7, 0.3))
    return 1;

  Eigen::Matrix<int, 2, 1> value1;
  value1(0) = 1;
  value1(1) = 0;
  std::cout << "pmf(1, 0): " << std::fixed << dist(value1) << std::endl
    << std::endl;
  if (fabs(dist(value1) - 0.7) > std::numeric_limits<double>::epsilon())
    return 1;
  value1(0) = 0;
  value1(1) = 1;
  std::cout << "pmf(0, 1): " << std::fixed << dist(value1) << std::endl
    << std::endl;
  if (fabs(dist(value1) - 0.3) > std::numeric_limits<double>::epsilon())
    return 1;
  value1(0) = 0;
  value1(1) = 2;
  std::cout << "pmf(0, 2): " << std::fixed << dist(value1) << std::endl
    << std::endl;
  if (fabs(dist(value1)) > std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.getProbability(2): " << std::endl;
    std::cout << dist.getProbability(2) << std::endl << std::endl;
  }
  catch (OutOfBoundException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist.setProbabilities(0.8, 0.9)" << std::endl;
    dist.setProbabilities(Eigen::Vector2d(0.8, 0.9));
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "dist.setNumTrials(5)" << std::endl << std::endl;
    dist.setNumTrials(5);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;

  std::vector<Eigen::Matrix<int, 2, 1> > samples;
  dist.getSamples(samples, 10);

  std::cout << "dist.getSamples(samples, 10): " << std::endl;

  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  CategoricalDistribution<2> distCopy(dist);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getProbabilities() != dist.getProbabilities())
    return 1;
  CategoricalDistribution<2> distAssign = dist;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getProbabilities() != dist.getProbabilities())
    return 1;

  std::cout << "Testing categorical distribution M-D" << std::endl;
  CategoricalDistribution<Eigen::Dynamic> distMd(Eigen::Matrix<double,
    Eigen::Dynamic, 1>::Constant(5, 1.0 / 5.0));
  std::cout << "Distribution parameters: " << std::endl << distMd
    << std::endl << std::endl;

  std::cout << "distMd.getProbabilities(): " << std::endl
    << distMd.getProbabilities() << std::endl << std::endl;
  std::cout << "distMd.getProbability(0): "
    << distMd.getProbability(0) << std::endl << std::endl;
  std::cout << "distMd.getProbability(1): "
    << distMd.getProbability(1) << std::endl << std::endl;
  std::cout << "distMd.getProbability(2): "
    << distMd.getProbability(2) << std::endl << std::endl;
  std::cout << "distMd.getProbability(3): "
    << distMd.getProbability(3) << std::endl << std::endl;
  std::cout << "distMd.getProbability(4): "
    << distMd.getProbability(4) << std::endl << std::endl;

  std::cout << "distMd.setProbabilities(0.1, 0.2, 0.3, 0.1, 0.3)"
    << std::endl << std::endl;
  Eigen::Matrix<double, Eigen::Dynamic, 1> probabilities(5);
  probabilities(0) = 0.1;
  probabilities(1) = 0.2;
  probabilities(2) = 0.3;
  probabilities(3) = 0.1;
  probabilities(4) = 0.3;
  distMd.setProbabilities(probabilities);
  std::cout << "Distribution new parameters: " << std::endl << distMd
    << std::endl << std::endl;
  if (distMd.getProbabilities() != probabilities)
    return 1;

  Eigen::Matrix<int, Eigen::Dynamic, 1> value(5);
  value(0) = 0;
  value(1) = 0;
  value(2) = 0;
  value(3) = 0;
  value(4) = 1;
  std::cout << "pmf(0, 0, 0, 0, 1): " << std::fixed << distMd(value)
    << std::endl << std::endl;
  if (fabs(distMd(value) - 0.3) > std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "distMd.getProbability(6): " << std::endl;
    std::cout << distMd.getProbability(6) << std::endl << std::endl;
  }
  catch (OutOfBoundException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  probabilities(0) = 0.1;
  probabilities(1) = 0.2;
  probabilities(2) = 0.3;
  probabilities(3) = 0.1;
  probabilities(4) = 0.4;
  try {
    std::cout << "distMd.setProbabilities(0.1, 0.2, 0.3, 0.1, 0.4)"
      << std::endl;
    distMd.setProbabilities(probabilities);
  }
  catch (BadArgumentException<Eigen::Matrix<double, Eigen::Dynamic, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;
  try {
    std::cout << "distMd.setNumTrials(5)" << std::endl << std::endl;
    distMd.setNumTrials(5);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "distMd.getSample(): " << std::endl << distMd.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<int, Eigen::Dynamic, 1> > samplesMd;
  distMd.getSamples(samplesMd, 10);
  std::cout << "distMd.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samplesMd[i] << std::endl;
  std::cout << std::endl;

  CategoricalDistribution<Eigen::Dynamic> distMdCopy(distMd);
  std::cout << "Copy constructor: " << std::endl << distMdCopy << std::endl
    << std::endl;
  if (distMdCopy.getProbabilities() != distMd.getProbabilities())
    return 1;
  CategoricalDistribution<Eigen::Dynamic> distMdAssign = distMd;
  std::cout << "Assignment operator: " << std::endl << distMdAssign
    << std::endl;
  if (distMdAssign.getProbabilities() != distMd.getProbabilities())
    return 1;

  return 0;
}
