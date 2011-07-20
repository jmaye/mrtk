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

/** \file GammaDistributionPlot.cpp
    \brief This file is a testing binary for plotting the gamma distribution pdf
  */

#include "visualization/ContinuousFunctionPlot.h"
#include "statistics/GammaDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  Eigen::Matrix<double, 1, 1> minimum;
  minimum(0) = 0;
  Eigen::Matrix<double, 1, 1> maximum;
  maximum(0) = 5;
  QApplication app(argc, argv);
  ContinuousFunctionPlot<double, double> plot("GammaDistribution",
    GammaDistribution<>(), minimum, maximum, 0.1);
  plot.show();
  return app.exec();
}
