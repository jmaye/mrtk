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

/** \file GUI2d.cpp
    \brief This file is a testing binary for a 2d GUI
  */

#include <QtGui/QApplication>

#include "visualization/MainWindow.h"
#include "visualization/View2d.h"
#include "visualization/View2dControl.h"
#include "visualization/ImageControl.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.setWindowTitle("A simple 2d GUI");
  mainWindow.addView(QString("2d"), View2d::getInstance());
  mainWindow.addControl(QString("View2d"), View2dControl::getInstance());
  mainWindow.addControl(QString("Image"), ImageControl::getInstance());
  mainWindow.show();
  return app.exec();
}
