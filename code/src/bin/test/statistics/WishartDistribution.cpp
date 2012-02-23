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

/** \file WishartDistribution.cpp
    \brief This file is a testing binary for the WishartDistribution class
  */

#include <iostream>

#include "statistics/WishartDistribution.h"

int main(int argc, char** argv) {
  WishartDistribution<2> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getDegrees(): " << dist.getDegrees() << std::endl;
  std::cout << "dist.getScale(): " << std::endl << dist.getScale() << std::endl;
  std::cout << "dist.getInverseScale(): " << std::endl << dist.getInverseScale()
    << std::endl;
  std::cout << "dist.getDeterminant(): " << dist.getDeterminant() << std::endl;
  std::cout << "dist.getNormalizer(): " << dist.getNormalizer() << std::endl;
  std::cout << "dist.getTransformation(): " << std::endl <<
    dist.getTransformation().matrixL() << std::endl;
  std::cout << "dist.setDegrees(3)" << std::endl;
  dist.setDegrees(3);
  std::cout << "dist.setScale((1, 0, 0, 1))" << std::endl;
  dist.setScale((Eigen::Matrix<double, 2, 2>() << 1, 0, 0, 1).finished());
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.pdf((1,0,0,1)): "
    << dist((Eigen::Matrix<double, 2, 2>() << 1, 0, 0, 1).finished())
    << std::endl;
  if (fabs(dist((Eigen::Matrix<double, 2, 2>() << 1, 0, 0, 1).finished()) -
    0.02927492) > 1e-4)
    return 1;
  std::cout << "dist.pdf((1,0,0,1)): "
    << dist((Eigen::Matrix<double, 2, 2>() << 2, 0, 0, 2).finished())
    << std::endl;
  if (fabs(dist((Eigen::Matrix<double, 2, 2>() << 2, 0, 0, 2).finished()) -
    0.01076964) > 1e-4)
    return 1;
  try {
    dist.setDegrees(1);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    dist.setScale((Eigen::Matrix<double, 2, 2>() << 10, 10, 10, 10).finished());
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 2> >& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;

  std::cout << "Testing Wishart distribution M-D" << std::endl;
  WishartDistribution<Eigen::Dynamic> distMd(6,
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Identity(4, 4));
  std::cout << "distMd.getSample(): " << std::endl << distMd.getSample()
    << std::endl;
  std::cout << "distMd.getMean(): " << std::endl << distMd.getMean()
    << std::endl;
  std::cout << "distMd.getMode(): " << std::endl << distMd.getMode()
    << std::endl;

  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> sampleMean =
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Zero(4, 4);
  for (size_t i = 0; i < 1000; ++i)
    sampleMean += distMd.getSample();
  sampleMean /= 1000;
  std::cout << "sample mean: " << std::endl << sampleMean << std::endl;

  return 0;
}
