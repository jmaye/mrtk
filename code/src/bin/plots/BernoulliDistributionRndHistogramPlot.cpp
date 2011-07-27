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

/** \file BernoulliDistributionRndHistogramPlot.cpp
    \brief This file is a testing binary for plotting random samples from the 
           BernoulliDistribution class
  */

#include "visualization/HistogramPlot.h"
#include "statistics/BernoulliDistribution.h"

#include <QtGui/QApplication>
// TODO: MEAN VALUE WRONG
int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<size_t, 1> histogram(0, 10, 1);
  BernoulliDistribution dist(0.1);
  for (size_t i = 0; i < 100000; ++i) {
    Eigen::Matrix<size_t, 2, 1> sample = dist.getSample();
    for (size_t j = 0; j < 2; ++j)
      histogram.setBinContent(j, histogram.getBinContent(j) + sample(j));
  }
  std::cout << histogram.getMeanValue() << std::endl;
  std::cout << histogram.getVariance() << std::endl;
  histogram.normalize();
  HistogramPlot<size_t, 1> plot("BernoulliDistributionRndHistogramPlot",
    histogram);
  plot.show();
  return app.exec();
}
