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

/** \file GammaDistributionSIR.cpp
    \brief This file is a testing binary for plotting random samples of the
           GammaDistribution class with sampling-importance-resampling.
  */

#include <QtGui/QApplication>

#include "visualization/HistogramPlot.h"
#include "statistics/SamplingImportanceResampler.h"
#include "statistics/GammaDistribution.h"
#include "statistics/CauchyDistribution.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<double, 1> hist(0, 100, 0.05);
  GammaDistribution<> dist(2.0, 2.0);
  CauchyDistribution cauchyDist(1.0, 2.0);
  std::vector<double> propSamples;
  std::vector<double> targetSamples;
  std::vector<double> weights;
  const size_t numSamples = 10000;
  SamplingImportanceResampler::getSamples(dist, cauchyDist, weights,
    propSamples, targetSamples, numSamples);
  hist.addSamples(targetSamples);
  std::cout << "Sample mean: " << hist.getMean() << std::endl;
  std::cout << "Sample mode: " << hist.getMode() << std::endl;
  std::cout << "Sample variance: " << hist.getVariance() << std::endl;
  std::cout << "Dist. mean: " << dist.getMean() << std::endl;
  std::cout << "Dist. mode: " << dist.getMode() << std::endl;
  std::cout << "Dist. variance: " << dist.getVariance() << std::endl;
  HistogramPlot<double, 1> plot("GammaDistributionSIR",
    hist.getNormalized());
  plot.show();
  return app.exec();
}
