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

/** \file MainWindow.h
    \brief This file contains a main window for Qt
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class Ui_MainWindow;

/** The MainWindow class is a main window for Qt.
    \brief Qt main window
  */
class MainWindow :
  public QMainWindow {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  MainWindow(const MainWindow& other);
  /// Assignment operator
  MainWindow& operator = (const MainWindow& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  MainWindow();
  /// Destructor
  ~MainWindow();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_MainWindow* mpUi;
  /** @}
    */

};

#endif // MAINWINDOW_H
