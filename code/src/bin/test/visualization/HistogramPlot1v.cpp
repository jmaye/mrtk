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

/** \file HistogramPlot1v.cpp
    \brief This file is a testing binary for the HistogramPlot1v class
  */

#include <iostream>

#include <QtGui/QApplication>

#include "visualization/HistogramPlot.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Histogram<size_t, 1> histogram;
  histogram.setBinContent(0, 10);
  histogram.setBinContent(1, 5);
  HistogramPlot<size_t, 1> plot("HistogramPlot1v", histogram);
  app.closeAllWindows();
  return 0;
}
