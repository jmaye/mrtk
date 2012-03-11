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

/** \file NormalScaledInvChiSquareDistributionRndScatterPlot.cpp
    \brief This file is a testing binary for plotting random samples of the 
           NormalScaledInvChiSquareDistribution class
  */

#include <QtGui/QApplication>

#include "visualization/ScatterPlot.h"
#include "statistics/NormalScaledInvChiSquareDistribution.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<Eigen::Matrix<double, 2, 1> > data;
  std::vector<NormalScaledInvChiSquareDistribution::RandomVariable> dataTuple;
  NormalScaledInvChiSquareDistribution dist(5, 1000, 1000, 2.0);
  data.reserve(10000);
  for (size_t i = 0; i < 10000; ++i) {
    NormalScaledInvChiSquareDistribution::RandomVariable sample =
      dist.getSample();
    data.push_back(Eigen::Matrix<double, 2, 1>(std::get<0>(sample),
      std::get<1>(sample)));
  }
  ScatterPlot<2> plot("NormalScaledInvChiSquareDistributionRndScatterPlot",
    data);
  plot.show();
  return app.exec();
}
