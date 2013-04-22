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

/** \file LogisticDistributionRndHistogramPlot1v.cpp
    \brief This file is a testing binary for plotting random samples of the
           LogisticDistribution
  */

#include <QtGui/QApplication>

#include "visualization/HistogramPlot.h"
#include "statistics/LogisticDistribution.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<double, 1> hist(-10, 10, 0.05);
  LogisticDistribution dist(1.0, 2.0);
  std::vector<double> data;
  dist.getSamples(data, 100000);
  hist.addSamples(data);
  std::cout << "Sample mean: " << hist.getMean() << std::endl;
  std::cout << "Sample median: " << hist.getMedian() << std::endl;
  std::cout << "Sample mode: " << hist.getMode() << std::endl;
  std::cout << "Sample variance: " << hist.getVariance() << std::endl;
  std::cout << "Dist. mean: " << dist.getMean() << std::endl;
  std::cout << "Dist. median: " << dist.getMedian() << std::endl;
  std::cout << "Dist. mode: " << dist.getMode() << std::endl;
  std::cout << "Dist. variance: " << dist.getVariance() << std::endl;
  HistogramPlot<double, 1> plot("LogisticDistributionRndHistogramPlot",
    hist.getNormalized());
  plot.show();
  return app.exec();
}
