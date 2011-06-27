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

/** \file ContinuousFunctionPlot1d.h
    \brief This file contains a plotting tool for 1-dimensional continuous
           functions
  */

#ifndef CONTINUOUSFUNCTIONPLOT1D_H
#define CONTINUOUSFUNCTIONPLOT1D_H

#include "visualization/FunctionPlot.h"

#include <QtGui/QWidget>
#include <QtCore/QVector>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>

/** The ContinuousFunctionPlot1d class is a plotting tool for 1-dimensional
    continuous functions
    \brief 1-d continuous function plotting tool
  */
template <typename Y, typename X, size_t M = 1> class ContinuousFunctionPlot;
template <typename Y, typename X> class ContinuousFunctionPlot<Y, X> :
  public FunctionPlot<Y, X, 1>,
  public QWidget {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  ContinuousFunctionPlot();
  /// Destructor
  virtual ~ContinuousFunctionPlot();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /** @}
    */

protected:
  QwtPlot* mpPlot;
  QwtPlotCurve* mCurve;
  QVector<X> mXData;
  QVector<Y> myData;

};

#include "visualization/ContinuousFunctionPlot1d.tpp"

#endif // CONTINUOUSFUNCTIONPLOT1D_H
