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

/** \file MultinomialDistributionRndHistogramPlot.cpp
    \brief This file is a testing binary for plotting random samples of the
           MultinomialDistribution class
  */

#include "visualization/HistogramPlot.h"
#include "statistics/MultinomialDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<size_t, 1> histogram(0, 10, 1);
  MultinomialDistribution<5> dist(20, (Eigen::Matrix<double, 5, 1>()
    << 0.1, 0.2, 0.2, 0.4, 0.1).finished());
  for (size_t i = 0; i < 100000; ++i) {
    Eigen::Matrix<size_t, 5, 1> sample = dist.getSample();
    for (size_t j = 0; j < 5; ++j)
      histogram.setBinContent(j, histogram.getBinContent(j) + sample(j));
  }
  std::cout << histogram.getMeanValue() << std::endl;
  std::cout << histogram.getVariance() << std::endl;
  histogram.normalize();
  HistogramPlot<size_t, 1> plot("MultinomialDistributionRndHistogramPlot",
    histogram);
  plot.show();
  return app.exec();
}
