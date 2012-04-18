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

/** \file GammaDistributionAdaptiveRejectionSampler.cpp
    \brief This file is a testing binary for plotting random samples of the
           GammaDistribution class with adaptive rejection sampling
  */

#include <QtGui/QApplication>

#include "visualization/HistogramPlot.h"
#include "statistics/AdaptiveRejectionSampler.h"
#include "statistics/GammaDistribution.h"

class LogPdf :
  public Function<double, double> {
public:
  virtual double getValue(const double& argument) const
      throw (BadArgumentException<double>) {
    static const GammaDistribution<> gammaDist(9.0, 2.0);
    return gammaDist.logpdf(argument);
  }
};

class LogPdfPrime :
  public Function<double, double> {
public:
  virtual double getValue(const double& argument) const
    throw (BadArgumentException<double>) {
    return 8.0 / argument - 2.0;
  }
};

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<double, 1> hist(0, 100, 0.05);
  std::vector<double> initPoints;
  initPoints.push_back(2.0);
  initPoints.push_back(8.0);
  std::vector<double> data;
  AdaptiveRejectionSampler::getSamples<double, double>(LogPdf(), LogPdfPrime(),
    initPoints, data, 100000, 0.0, std::numeric_limits<double>::infinity());
  hist.addSamples(data);
  GammaDistribution<> dist(9.0, 2.0);
  std::cout << "Sample mean: " << hist.getMean() << std::endl;
  std::cout << "Sample mode: " << hist.getMode() << std::endl;
  std::cout << "Sample variance: " << hist.getVariance() << std::endl;
  std::cout << "Dist. mean: " << dist.getMean() << std::endl;
  std::cout << "Dist. mode: " << dist.getMode() << std::endl;
  std::cout << "Dist. variance: " << dist.getVariance() << std::endl;
  HistogramPlot<double, 1> plot("GammaDistributionAdaptiveRejectionSampler",
    hist.getNormalized());
  plot.show();
  return app.exec();
}
