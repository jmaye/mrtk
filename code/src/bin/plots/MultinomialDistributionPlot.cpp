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

/** \file MultinomialDistributionPlot.cpp
    \brief This file is a testing binary for plotting the multinomial
           distribution pmf
  */

#include "visualization/DiscreteFunctionPlot.h"
#include "statistics/MultinomialDistribution.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  Eigen::Matrix<size_t, 2, 1> minimum(0, 0);
  Eigen::Matrix<size_t, 2, 1> maximum(20, 20);
  QApplication app(argc, argv);
  DiscreteFunctionPlot<double, size_t, 2> plot("MultinomialDistribution",
    MultinomialDistribution<3>(20), minimum, maximum);
  plot.show();
  return app.exec();
}
