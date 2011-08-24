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

/** \file DirichletDistributionRndScatterPlot3v.cpp
    \brief This file is a testing binary for plotting random samples of the
           Dirichlet3v distribution
  */

#include "visualization/ScatterPlot.h"
#include "statistics/DirichletDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<Eigen::Matrix<double, 3, 1> > data;
  DirichletDistribution<3> dist;
  for (size_t i = 0; i < 100000; ++i)
    data.push_back(dist.getSample());
  ScatterPlot<3> plot("DirichletDistributionRndScatterPlot3v", data);
  plot.show();
  return app.exec();
}
