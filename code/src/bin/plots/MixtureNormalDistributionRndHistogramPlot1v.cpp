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

/** \file MixtureNormalDistributionRndHistogramPlot1v.cpp
    \brief This file is a testing binary for plotting random samples from a
           mixture of univariate normal distributions
  */

#include "visualization/HistogramPlot.h"
#include "statistics/NormalDistribution.h"
#include "statistics/MixtureSampleDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  std::vector<NormalDistribution<1> > distributions;
  distributions.push_back(NormalDistribution<1>(0, 1));
  distributions.push_back(NormalDistribution<1>(5, 1));
  distributions.push_back(NormalDistribution<1>(10, 1));
  distributions.push_back(NormalDistribution<1>(-5, 1));
  distributions.push_back(NormalDistribution<1>(-10, 1));
  MixtureSampleDistribution<NormalDistribution<1>, 5> dist(distributions,
    CategoricalDistribution<5>());
  Histogram<double, 1> hist(-20, 20, 0.05);
  for (size_t i = 0; i < 100000; ++i)
    hist.addSample(dist.getSample());
  hist.normalize();
  HistogramPlot<double, 1> plot("MixtureNormalDistributionRndHistogramPlot1v",
    hist);
  plot.show();
  return app.exec();
}
