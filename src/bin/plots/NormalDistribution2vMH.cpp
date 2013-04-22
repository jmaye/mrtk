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

/** \file NormalDistribution2vMH.cpp
    \brief This file is a testing binary for plotting random samples of the 
           NormalDistribution2v class using Metropolis-Hastings
  */

#include <QtGui/QApplication>

#include "visualization/ScatterPlot.h"
#include "statistics/NormalDistribution.h"
#include "statistics/MetropolisHastingsSampler.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<Eigen::Matrix<double, 2, 1> > data;
  NormalDistribution<2> dist(Eigen::Matrix<double, 2, 1>(1.0, 1.0),
    (Eigen::Matrix<double, 2, 2>() << 2, 0, 0, 2).finished());
  NormalDistribution<2> proposal(Eigen::Matrix<double, 2, 1>(10.0, 10.0),
    Eigen::Matrix<double, 2, 2>::Identity() * 0.5);
  MetropolisHastingsSampler::getSamples<double, double, 2>(dist, proposal, data,
    10000);
  ScatterPlot<2> plot("NormalDistribution2vMH", data);
  plot.show();
  return app.exec();
}
