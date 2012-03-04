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

/** \file DiscreteFunctionPlot1v.cpp
    \brief This file is a testing binary for the discrete FunctionPlot1v class
  */

#include <iostream>

#include <QtGui/QApplication>

#include "visualization/FunctionPlot.h"
#include "statistics/PoissonDistribution.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  FunctionPlot<PoissonDistribution> plot("PoissonDistribution",
    PoissonDistribution(2.5), 0, 10, 1);
  std::cout << "Title: " << plot.getTitle() << std::endl;
  std::cout << "Minimum: " << plot.getMinimum() << std::endl;
  std::cout << "Maximum: " << plot.getMaximum() << std::endl;
  std::cout << "Resolution: " << plot.getResolution() << std::endl;
  app.closeAllWindows();
  return 0;
}
