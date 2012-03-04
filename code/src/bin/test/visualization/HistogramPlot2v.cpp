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

/** \file HistogramPlot2v.cpp
    \brief This file is a testing binary for the HistogramPlot2v class
  */

#include <iostream>

#include <QtGui/QApplication>

#include "visualization/HistogramPlot.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<double, 2> histogram(Eigen::Matrix<double, 2, 1>(0, 0),
    Eigen::Matrix<double, 2, 1>(3, 3),
    Eigen::Matrix<double, 2, 1>(1.0, 1.0));
  histogram.addSample(Eigen::Matrix<double, 2, 1>(2.5, 2.0));
  histogram.addSample(Eigen::Matrix<double, 2, 1>(3.0, 3.0));
  HistogramPlot<double, 2> plot("HistogramPlot2v", histogram);
  app.closeAllWindows();
  return 0;
}
