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

/** \file UniformDistribution.cpp
    \brief This file is a testing binary for the UniformDistribution class
  */

#include "statistics/UniformDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing continuous uniform distribution" << std::endl;
  UniformDistribution<double> distCont;
  std::cout << "Distribution default parameters: " << std::endl << distCont
    << std::endl << std::endl;
  std::cout << "dist.getMinSupport(): " << distCont.getMinSupport() << std::endl
    << std::endl;
  std::cout << "dist.getMaxSupport(): " << distCont.getMaxSupport() << std::endl
    << std::endl;
  std::cout << "dist.setSupport(2, 5)" << std::endl << std::endl;
  distCont.setSupport(2, 5);
  std::cout << "Distribution new parameters: " << std::endl << distCont
    << std::endl << std::endl;

  std::cout << "pdf(2): " << std::fixed << distCont(2) << std::endl
    << std::endl;
  if (fabs(distCont(2) - 1.0 / 3.0) > 1e-4)
    return 1;

  std::cout << "pdf(5): " << std::fixed << distCont(5) << std::endl
    << std::endl;
  if (fabs(distCont(5) -  1.0 / 3.0) > 1e-4)
    return 1;

  std::cout << "pdf(3): " << std::fixed << distCont(3) << std::endl
    << std::endl;
  if (fabs(distCont(3) -  1.0 / 3.0) > 1e-4)
    return 1;

  std::cout << "pdf(10): " << std::fixed << distCont(10) << std::endl
    << std::endl;
  if (fabs(distCont(10) - 0.0) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << std::endl << distCont.getSample()
    << std::endl << std::endl;

  std::cout << "Testing discrete uniform distribution" << std::endl;
  UniformDistribution<ssize_t> distDisc;
  std::cout << "Distribution default parameters: " << std::endl << distDisc
    << std::endl << std::endl;
  std::cout << "dist.getMinSupport(): " << distDisc.getMinSupport() << std::endl
    << std::endl;
  std::cout << "dist.getMaxSupport(): " << distDisc.getMaxSupport() << std::endl
    << std::endl;
  std::cout << "dist.setSupport(2, 5)" << std::endl << std::endl;
  distDisc.setSupport(2, 5);
  std::cout << "Distribution new parameters: " << std::endl << distDisc
    << std::endl << std::endl;

  std::cout << "pdf(2): " << std::fixed << distDisc(2) << std::endl
    << std::endl;
  if (fabs(distDisc(2) - 1.0 / 3.0) > 1e-4)
    return 1;

  std::cout << "pdf(5): " << std::fixed << distDisc(5) << std::endl
    << std::endl;
  if (fabs(distDisc(5) -  1.0 / 3.0) > 1e-4)
    return 1;

  std::cout << "pdf(3): " << std::fixed << distDisc(3) << std::endl
    << std::endl;
  if (fabs(distDisc(3) -  1.0 / 3.0) > 1e-4)
    return 1;

  std::cout << "pdf(10): " << std::fixed << distDisc(10) << std::endl
    << std::endl;
  if (fabs(distDisc(10) - 0.0) > 1e-4)
    return 1;

  std::cout << "dist.getSample(): " << std::endl << distDisc.getSample()
    << std::endl << std::endl;

  return 0;
}
