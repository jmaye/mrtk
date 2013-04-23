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

/** \file ScaledInvChiSquareDistributionRndHistogramPlot.cpp
    \brief This file is a testing binary for plotting random samples of the
           ScaledInvChiSquareDistribution class
  */

#include <QtGui/QApplication>

#include "visualization/HistogramPlot.h"
#include "statistics/ScaledInvChiSquareDistribution.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<double, 1> hist(0, 1000, 0.05);
  ScaledInvChiSquareDistribution dist(5, 4);
  std::vector<double> data;
  dist.getSamples(data, 100000);
  hist.addSamples(data);
  std::cout << "Sample mean: " << hist.getMean() << std::endl;
  std::cout << "Sample median: " << hist.getMedian() << std::endl;
  std::cout << "Sample mode: " << hist.getMode() << std::endl;
  std::cout << "Sample variance: " << hist.getVariance() << std::endl;
  std::cout << "Dist. mean: " << dist.getMean() << std::endl;
  std::cout << "Dist. mode: " << dist.getMode() << std::endl;
  std::cout << "Dist. variance: " << dist.getVariance() << std::endl;
  std::cout << "Dist degrees: " << dist.getDegrees() << std::endl;
  std::cout << "Dist scale: " << dist.getScale() << std::endl;
  HistogramPlot<double, 1> plot(
    "ScaledInvChiSquareDistributionRndHistogramPlot", hist.getNormalized());
  plot.show();
  return app.exec();
}