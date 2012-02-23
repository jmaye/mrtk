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

#include <iostream>

#include "statistics/BetaDistribution.h"

int main(int argc, char** argv) {
  double alpha = 0.1;
  double beta = 0.9;
  BetaDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getAlpha(): " << dist.getAlpha() << std::endl << std::endl;
  std::cout << "dist.getBeta(): " << dist.getBeta() << std::endl << std::endl;
  std::cout << "dist.setAlpha(0.1)" << std::endl << std::endl;
  std::cout << "dist.setBeta(0.9)" << std::endl << std::endl;
  dist.setAlpha(alpha);
  dist.setBeta(beta);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getAlpha(): " << dist.getAlpha() << std::endl << std::endl;
  std::cout << "dist.getBeta(): " << dist.getBeta() << std::endl << std::endl;

  std::cout << "pdf(0.1): " << std::fixed << dist(0.1) << std::endl
    << std::endl;
  if (fabs(dist(0.1) - 0.7896) > 1e-4)
    return 1;
  std::cout << "pdf(0.9): " << std::fixed << dist(0.9) << std::endl
    << std::endl;
  if (fabs(dist(0.9) - 0.1361) > 1e-4)
    return 1;

  std::cout << "logpdf(0.1): " << std::fixed << dist.logpdf(0.1) << std::endl
    << std::endl;
  if (fabs(dist.logpdf(0.1) + 0.2362263) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << std::endl << dist.getSample()
    << std::endl << std::endl;

  try {
    alpha = 0.0;
    dist.setAlpha(alpha);
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
