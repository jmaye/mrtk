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

/** \file ExponentialDistributionRndHistogramPlot.cpp
    \brief This file is a testing binary for plotting random samples of the
           ExponentialDistribution class
  */

#include "visualization/HistogramPlot.h"
#include "statistics/ExponentialDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<double, 1> histogram(-2, 8, 0.05);
  ExponentialDistribution dist;
  for (size_t i = 0; i < 100000; ++i)
    histogram.addSample(dist.getSample());
  histogram.normalize();
  HistogramPlot<double, 1> plot("ExponentialDistributionRndHistogramPlot",
    histogram);
  plot.show();
  return app.exec();
}
