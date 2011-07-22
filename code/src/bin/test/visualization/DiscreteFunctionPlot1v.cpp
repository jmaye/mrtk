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
    \brief This file is a testing binary for the DiscreteFunctionPlot1v class
  */

#include "visualization/DiscreteFunctionPlot.h"
#include "functions/FactorialFunction.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  DiscreteFunctionPlot<size_t, size_t, 1> plot("FactorialFunction",
    FactorialFunction(), 0, 10);
  try {
    DiscreteFunctionPlot<size_t, size_t, 1> plotWrong1("FactorialFunction",
      FactorialFunction(), 10, 0);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  app.closeAllWindows();
  return 0;
}
