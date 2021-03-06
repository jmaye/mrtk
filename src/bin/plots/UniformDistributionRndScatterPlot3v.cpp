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

/** \file UniformDistributionRndScatterPlot3v.cpp
    \brief This file is a testing binary for plotting random samples of the 
           UniformDistribution3v class
  */

#include <QtGui/QApplication>

#include "visualization/ScatterPlot.h"
#include "statistics/UniformDistribution.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<Eigen::Matrix<double, 3, 1> > data;
  UniformDistribution<double, 3> dist;
  dist.getSamples(data, 100000);
  ScatterPlot<3> plot("UniformDistributionRndScatterPlot3v", data);
  plot.show();
  return app.exec();
}
