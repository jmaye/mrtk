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

/** \file ContinuousFunctionPlot2v.cpp
    \brief This file is a testing binary for the ContinuousFunctionPlot2v class
  */

#include "visualization/ContinuousFunctionPlot.h"
#include "statistics/NormalDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  Eigen::Matrix<double, 2, 1> minimum(-2, -2);
  Eigen::Matrix<double, 2, 1> maximum(2, 2);
  Eigen::Matrix<double, 2, 1> resolution(0.05, 0.05);
  QApplication app(argc, argv);
  ContinuousFunctionPlot<double, double, 2> plot("NormalDistribution2v",
    NormalDistribution<2>(), minimum, maximum, resolution);
  app.closeAllWindows();
  return 0;
}
