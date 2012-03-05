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

#include <QtGui/QApplication>

#include "visualization/HistogramPlot.h"
#include "statistics/MultinomialDistribution.h"
#include "statistics/Randomizer.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<int, 1> hist(0, 10, 1);
  MultinomialDistribution<5> dist(20, (Eigen::Matrix<double, 5, 1>()
    << 0.1, 0.2, 0.2, 0.4, 0.1).finished());
  Randomizer<double, 5> randomizer;
  for (size_t i = 0; i < 100000; ++i)
    hist.addSample(randomizer.sampleCategorical((Eigen::Matrix<double, 5, 1>()
    << 0.1, 0.2, 0.2, 0.4, 0.1).finished()));
  HistogramPlot<int, 1> plot("MultinomialDistributionRndHistogramPlot",
    hist.getNormalized());
  plot.show();
  return app.exec();
}
