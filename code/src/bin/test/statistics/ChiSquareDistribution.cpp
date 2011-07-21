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

/** \file ChiSquareDistribution.cpp
    \brief This file is a testing binary for the ChiSquareDistribution class
  */

#include "statistics/ChiSquareDistribution.h"

int main(int argc, char** argv) {
  ChiSquareDistribution dist;
  std::cout << "Distribution default parameters: " << std::endl << dist
    << std::endl << std::endl;
  std::cout << "dist.getDegrees(): " << dist.getDegrees() << std::endl
    << std::endl;
  std::cout << "dist.setDegrees(2)" << std::endl << std::endl;
  dist.setDegrees(2);

  std::cout << "Distribution new parameters: " << std::endl << dist
    << std::endl << std::endl;

  std::cout << "pdf(0.5): " << std::fixed << dist(0.5) << std::endl
    << std::endl;
  if (fabs(dist(0.5) - 0.3894004 ) > 1e-4)
    return 1;

  std::cout << "pdf(1.5): " << std::fixed << dist(1.5) << std::endl
    << std::endl;
  if (fabs(dist(1.5) - 0.2361833) > 1e-4)
    return 1;

  std::cout << "logpdf(1.5): " << std::fixed << dist.logpdf(1.5) << std::endl
    << std::endl;
  if (fabs(dist.logpdf(1.5) + 1.443147) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << dist.getSample() << std::endl
    << std::endl;

  try {
    dist.setDegrees(0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
