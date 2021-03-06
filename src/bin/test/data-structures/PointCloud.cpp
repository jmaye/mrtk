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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file PointCloud.cpp
    \brief This file is a testing binary for the PointCloud class.
  */

#include <iostream>

#include "data-structures/PointCloud.h"

int main (int argc, char** argv) {
  PointCloud<double, 3> p1;
  std::cout << "Adding a point: " << std::endl;
  p1.insertPoint(Eigen::Matrix<double, 3, 1>(0.0, 0.0, 0.1));
  std::cout << "Initial number of points: " << p1.getNumPoints() << std::endl;
  PointCloud<double, 3> p2;
  p2.insertPoint(Eigen::Matrix<double, 3, 1>(1.0, 0.0, 0.1));
  p1.merge(p2);
  std::cout << "Final number of points: " << p1.getNumPoints() << std::endl;
  return 0;
}
