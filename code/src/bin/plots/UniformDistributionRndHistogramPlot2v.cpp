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

/** \file UniformDistributionRndHistogramPlot2v.cpp
    \brief This file is a testing binary for plotting random samples of the 
           UniformDistribution2v class
  */

#include "visualization/HistogramPlot.h"
#include "statistics/UniformDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<double, 2> hist(Eigen::Matrix<double, 2, 1>(-10, -10),
    Eigen::Matrix<double, 2, 1>(10, 10),
    Eigen::Matrix<double, 2, 1>(0.05, 0.05));
  UniformDistribution<double, 2> dist;
  std::vector<Eigen::Matrix<double, 2, 1> > data;
  dist.getSamples(data, 100000);
  hist.addSamples(data);
  std::cout << "Sample mean: " << std::endl << hist.getSampleMean()
    << std::endl;
  std::cout << "Sample mode: " << std::endl
    << hist.getBinCenter(hist.getMaximumBin()) << std::endl;
  std::cout << "Sample covariance: " << std::endl << hist.getSampleCovariance()
    << std::endl;
  hist.normalize();
  HistogramPlot<double, 2> plot("UniformDistributionRndHistogramPlot2v", hist);
  plot.show();
  return app.exec();
}
