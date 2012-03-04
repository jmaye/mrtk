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

/** \file StudentDistribution1vPlotSave.cpp
    \brief This file is a testing binary for plotting the univariate Student
           distribution pdf and saving it to pdf
  */

#include "visualization/FunctionPlot.h"
#include "statistics/StudentDistribution.h"

#include <QtGui/QApplication>
#include <QtGui/QPrinter>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  FunctionPlot<StudentDistribution<> > plot("StudentDistribution1v",
    StudentDistribution<1>(), -5, 5, 0.1);
  plot.show();
  QPrinter printer(QPrinter::HighResolution);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOutputFileName("test.pdf");
  plot.print(printer);
  return app.exec();
}
