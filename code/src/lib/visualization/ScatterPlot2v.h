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

/** \file ScatterPlot2v.h
    \brief This file contains a plotting tool for bivariate scatter plots
  */

#ifndef SCATTERPLOT2V_H
#define SCATTERPLOT2V_H

#include <QtGui/QWidget>
#include <QtCore/QVector>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>

template <typename Y, typename X, size_t M> class ScatterPlot;

/** The ScatterPlot2v class is a plotting tool for bivariate scatter plots.
    \brief 2-v scatter plot
  */
template <typename Y, typename X> class ScatterPlot<Y, X, 2> :
  public QwtPlot {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  ScatterPlot(const std::string& title);
  /// Copy constructor
  ScatterPlot(const ScatterPlot<Y, X, 2>& other);
  /// Assignment operator
  ScatterPlot<Y, X, 2>& operator = (const ScatterPlot<Y, X, 2>& other);
  /// Destructor
  virtual ~ScatterPlot();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Show the plot
  virtual void show();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Curve plotted
  QwtPlotCurve mCurve;
  /// Grid
  QwtPlotGrid mGrid;
  /// Data on the x-axis
  QVector<X> mXData;
  /// Data on the y-axis
  QVector<Y> mYData;
  /** @}
    */

};

#include "visualization/ScatterPlot2v.tpp"

#endif // SCATTERPLOT2V_H