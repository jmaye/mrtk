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

/** \file LogisticDistribution.cpp
    \brief This file is a testing binary for the LogisticDistribution class
  */

#include "statistics/LogisticDistribution.h"

int main(int argc, char** argv) {
  LogisticDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getLocation(): " << dist.getLocation() << std::endl
    << std::endl;
  std::cout << "dist.getScale(): " << dist.getScale() << std::endl
    << std::endl;
  std::cout << "dist.getInverseScale(): " << dist.getInverseScale() << std::endl
    << std::endl;
  std::cout << "dist.getMean(): " << dist.getMean() << std::endl
    << std::endl;
  std::cout << "dist.getMedian(): " << dist.getMedian() << std::endl
    << std::endl;
  std::cout << "dist.getMode(): " << dist.getMode() << std::endl
    << std::endl;
  std::cout << "dist.getVariance(): " << dist.getVariance() << std::endl
    << std::endl;
  std::cout << "dist.setLocation(1)" << std::endl;
  dist.setLocation(1);
  std::cout << "dist.setScale(2)" << std::endl;
  dist.setScale(2);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "pdf(1): " << std::fixed << dist(1) << std::endl
    << std::endl;
  if (fabs(dist(1) - 0.125) > 1e-4)
    return 1;

  std::cout << "pdf(3): " << std::fixed << dist(3) << std::endl
    << std::endl;
  if (fabs(dist(3) - 0.09830597) > 1e-4)
    return 1;

  std::cout << "pdf(-1): " << std::fixed << dist(-1) << std::endl
    << std::endl;
  if (fabs(dist(-1) - 0.09830597) > 1e-4)
    return 1;

  std::cout << "logpdf(2): " << std::fixed << dist.logpdf(2) << std::endl
    << std::endl;
  if (fabs(dist.logpdf(2) + 2.141301) > 1e-4)
    return 1;

  std::cout << "cdf(1): " << std::fixed << dist.cdf(1) << std::endl
    << std::endl;
  if (fabs(dist.cdf(1) - 0.5) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << dist.getSample() << std::endl
    << std::endl;

  try {
    dist.setScale(0.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
