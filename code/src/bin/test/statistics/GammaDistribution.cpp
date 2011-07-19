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

/** \file GammaDistribution.cpp
    \brief This file is a testing binary for the GammaDistribution class
  */

#include "statistics/GammaDistribution.h"

int main(int argc, char** argv) {
  GammaDistribution<double> dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getShape(): " << dist.getShape() << std::endl << std::endl;
  std::cout << "dist.getScale(): " << dist.getScale() << std::endl << std::endl;
  std::cout << "dist.setShape(1.5)" << std::endl << std::endl;
  std::cout << "dist.setScale(0.5)" << std::endl << std::endl;
  dist.setShape(1.5);
  dist.setScale(0.5);
  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getShape(): " << dist.getShape() << std::endl << std::endl;
  std::cout << "dist.getScale(): " << dist.getScale() << std::endl << std::endl;

  std::cout << "pdf(0.5): " << std::fixed << dist(0.5) << std::endl
    << std::endl;
  if (fabs(dist(0.5) - 0.830215) > 1e-4)
    return 1;

  std::cout << "pdf(1.5): " << std::fixed << dist(1.5) << std::endl
    << std::endl;
  if (fabs(dist(1.5) - 0.1946087) > 1e-4)
    return 1;

  std::cout << "pdf(0): " << std::fixed << dist(0) << std::endl << std::endl;
  if (fabs(dist(0) - 0.0) > 1e-4)
    return 1;

  std::cout << "logpdf(1.5): " << std::fixed << dist.logpdf(1.5) << std::endl
    << std::endl;

  std::cout << "dist.getSample(): " << dist.getSample() << std::endl
    << std::endl;

  try {
    dist.setShape(0.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    dist.setScale(0.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
