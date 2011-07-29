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

/** \file NormalDistributionRndHistogramPlot2v.cpp
    \brief This file is a testing binary for plotting random samples of the 
           NormalDistribution2v class
  */

#include "visualization/HistogramPlot.h"
#include "statistics/NormalDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<double, 2> hist(Eigen::Matrix<double, 2, 1>(-10, -10),
    Eigen::Matrix<double, 2, 1>(10, 10),
    Eigen::Matrix<double, 2, 1>(0.05, 0.05));
  NormalDistribution<2> dist;
  for (size_t i = 0; i < 100000; ++i)
    hist.addSample(dist.getSample());
  std::cout << "Sample mean: " << std::endl << hist.getSampleMean()
    << std::endl;
  std::cout << "Sample mode: " << std::endl
    << hist.getBinCenter(hist.getMaximumBin()) << std::endl;
  std::cout << "Sample covariance: " << std::endl << hist.getSampleCovariance()
    << std::endl;
  std::cout << "Dist. mean: " << std::endl << dist.getMean() << std::endl;
  std::cout << "Dist. mode: " << std::endl << dist.getMode() << std::endl;
  std::cout << "Dist. covariance: " << std::endl << dist.getCovariance()
    << std::endl;
  hist.normalize();
  return app.exec();
}
