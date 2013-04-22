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

/** \file PCA.cpp
    \brief This file is a testing binary for the PCA class
  */

#include <iostream>

#include "ml/PCA.h"
#include "statistics/NormalDistribution.h"

int main(int argc, char** argv) {
  NormalDistribution<2> dist;
  std::vector<Eigen::Matrix<double, 2, 1> > samples;
  dist.getSamples(samples, 10000);

  std::vector<Eigen::Matrix<double, 2, 1> > transformedSamples;
  Eigen::Matrix<double, 2, 1> eigenValues;
  Eigen::Matrix<double, 2, 2> eigenVectors;

  PCA::analyze<double, 2, 2>(samples, transformedSamples, eigenValues,
    eigenVectors);

  std::cout << "Eigen values: " << std::endl << eigenValues << std::endl
    << std::endl;
  std::cout << "Eigen vectors: " << std::endl << eigenVectors << std::endl
    << std::endl;

  try {
    samples.clear();
    PCA::analyze<double, 2, 2>(samples, transformedSamples, eigenValues,
      eigenVectors);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
