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

/** \file Transformation.cpp
    \brief This file is a testing binary for the Transformation class.
  */

#include <iostream>

#include "geometry/Transformation.h"

int main (int argc, char** argv) {
  std::cout << "Testing transformation 2d" << std::endl;
  Transformation<double, 2> trans2d;
  std::cout << "Setting transformation to (1.0, 2.0, 1.5)" << std::endl;
  trans2d.setTransformation(1.0, 2.0, 1.5);
  std::cout << "Transformation matrix: " << std::endl
    << trans2d.getTransformationMatrix() << std::endl;
  Eigen::Matrix<double, 2, 1> point2d(1.0, 2.0);
  Eigen::Matrix<double, 2, 1> point2dTrans;
  std::cout << "Transforming point (1.0, 2.0): " << std::endl;
  trans2d.transform(point2d, point2dTrans);
  std::cout << point2dTrans << std::endl;
  std::cout << "Transforming point (1.0, 2.0) with operator: " << std::endl;
  std::cout << trans2d(point2d) << std::endl;
  std::cout << "Inversing transformation" << std::endl;
  trans2d.inverse();
  std::cout << "Retrieving original point: " << std::endl
    << trans2d(point2dTrans) << std::endl;

  std::cout << std::endl;
  std::cout << "Testing transformation 3d" << std::endl;
  Transformation<double, 3> trans3d;
  std::cout << "Setting transformation to (1.0, 2.0, 3.0, 1.5, 1.5, 1.5)"
    << std::endl;
  trans3d.setTransformation(1.0, 2.0, 3.0, 1.5, 1.5, 1.5);
  std::cout << "Transformation matrix: " << std::endl
    << trans3d.getTransformationMatrix() << std::endl;
  Eigen::Matrix<double, 3, 1> point3d(1.0, 2.0, 3.0);
  Eigen::Matrix<double, 3, 1> point3dTrans;
  std::cout << "Transforming point (1.0, 2.0, 3.0): " << std::endl;
  trans3d.transform(point3d, point3dTrans);
  std::cout << point3dTrans << std::endl;
  std::cout << "Transforming point (1.0, 2.0, 3.0) with operator: "
    << std::endl << trans3d(point3d) << std::endl;
  std::cout << "Inversing transformation" << std::endl;
  trans3d.inverse();
  std::cout << "Retrieving original point: " << std::endl
    << trans3d(point3dTrans) << std::endl;
  return 0;
}
