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

/** \file GUI3d.cpp
    \brief This file is a testing binary for a 3d GUI
  */

#include <QtGui/QApplication>

#include "visualization/MainWindow.h"
#include "visualization/View3d.h"
#include "visualization/View3dControl.h"
#include "visualization/PointCloudControl.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.setWindowTitle("A simple 3d GUI");
  mainWindow.addView(QString("3d"), View3d::getInstance());
  mainWindow.addControl(QString("View3d"), View3dControl::getInstance());
  mainWindow.addControl(QString("Pointcloud"),
    PointCloudControl::getInstance());
  mainWindow.show();
  return app.exec();
}
