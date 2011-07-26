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

/** \file HistogramPlot2v.h
    \brief This file contains a plotting tool for bivariate histogram plots
  */

#ifndef HISTOGRAMPLOT2V_H
#define HISTOGRAMPLOT2V_H

#include <qwtplot3d-qt4/qwt3d_surfaceplot.h>

template <typename Y, typename X, size_t M> class HistogramPlot;

/** The HistogramPlot2v class is a plotting tool for bivariate histogram plots.
    \brief 2-v histogram plot
  */
template <typename Y, typename X> class HistogramPlot<Y, X, 2> :
  public Qwt3D::SurfacePlot {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  HistogramPlot(const HistogramPlot<Y, X, 2>& other);
  /// Assignment operator
  HistogramPlot<Y, X, 2>& operator = (const HistogramPlot<Y, X, 2>& other);
  /** @}
    */
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  HistogramPlot(const std::string& title);
  /// Destructor
  virtual ~HistogramPlot();
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
  /// Data on to be plotted
  Y** mData;
  /** @}
    */

};

#include "visualization/HistogramPlot2v.tpp"

#endif // HISTOGRAMPLOT2V_H
