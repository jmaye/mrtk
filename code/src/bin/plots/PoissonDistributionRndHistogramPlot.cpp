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

/** \file PoissonDistributionRndHistogramPlot.cpp
    \brief This file is a testing binary for plotting random samples from the
           PoissonDistribution class
  */

#include <QtGui/QApplication>

#include "visualization/HistogramPlot.h"
#include "statistics/PoissonDistribution.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<int, 1> hist(0, 100, 1);
  PoissonDistribution dist(2.5);
  std::vector<int> data;
  dist.getSamples(data, 100000);
  hist.addSamples(data);
  std::cout << "Sample mean: " << hist.getSampleMean() << std::endl;
  std::cout << "Sample median: " << hist.getSampleMedian() << std::endl;
  std::cout << "Sample mode: " << hist.getBinCenter(hist.getMaximumBin())
    << std::endl;
  std::cout << "Sample variance: " << hist.getSampleVariance() << std::endl;
  std::cout << "Dist. mean: " << dist.getMean() << std::endl;
  std::cout << "Dist. median: " << dist.getMedian() << std::endl;
  std::cout << "Dist. mode: " << dist.getMode() << std::endl;
  std::cout << "Dist. variance: " << dist.getVariance() << std::endl;
  hist.normalize();
  HistogramPlot<int, 1> plot("PoissonDistributionRndHistogramPlot", hist);
  plot.show();
  return app.exec();
}
