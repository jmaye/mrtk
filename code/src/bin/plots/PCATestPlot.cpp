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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file PCATestPlot.cpp
    \brief This file is a testing binary for plotting PCA result
  */

#include <QtGui/QApplication>

#include "ml/PCA.h"
#include "statistics/NormalDistribution.h"
#include "statistics/CategoricalDistribution.h"
#include "statistics/MixtureSampleDistribution.h"
#include "visualization/ScatterPlot.h"
#include "visualization/HistogramPlot.h"

int main(int argc, char** argv) {
  std::vector<NormalDistribution<2> > distributions;
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(0, 0),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(5, 5),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(10, 10),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-5, -5),
    Eigen::Matrix<double, 2, 2>::Identity()));
  distributions.push_back(NormalDistribution<2>(
    Eigen::Matrix<double, 2, 1>(-10, -10),
    Eigen::Matrix<double, 2, 2>::Identity()));
  MixtureSampleDistribution<NormalDistribution<2>, 5> dist(distributions,
    CategoricalDistribution<5>());
  std::vector<Eigen::Matrix<double, 2, 1> > samples;
  dist.getSamples(samples, 10000);

  std::vector<Eigen::Matrix<double, 1, 1> > transformedSamples;
  Eigen::Matrix<double, 2, 1> eigenValues;
  Eigen::Matrix<double, 2, 2> eigenVectors;

  PCA::analyze<double, 2, 1>(samples, transformedSamples, eigenValues,
    eigenVectors);

  Histogram<double, 1> hist(-20, 20, 0.05);
  for (size_t i = 0; i < transformedSamples.size(); ++i)
    hist.addSample(transformedSamples[i](0));
//  hist.normalize();

  QApplication app(argc, argv);
  ScatterPlot<2> plotOriginal("Original Data", samples);
  HistogramPlot<double, 1> plotTransformed("Transformed Data", hist);
  plotOriginal.show();
  plotTransformed.show();
  return app.exec();

  return 0;
}
