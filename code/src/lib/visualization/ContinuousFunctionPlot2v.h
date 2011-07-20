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

/** \file ContinuousFunctionPlot2v.h
    \brief This file contains a plotting tool for bivariate continuous
           functions
  */

#ifndef CONTINUOUSFUNCTIONPLOT2V_H
#define CONTINUOUSFUNCTIONPLOT2V_H

#include "functions/ContinuousFunction.h"
#include "visualization/FunctionPlot.h"
#include "exceptions/BadArgumentException.h"

#include <qwtplot3d-qt4/qwt3d_surfaceplot.h>

#include <vector>

template <typename Y, typename X, size_t M> class ContinuousFunctionPlot;

/** The ContinuousFunctionPlot1v class is a plotting tool for univariate
    continuous functions.
    \brief 1-v continuous function plotting tool
  */
template <typename Y, typename X> class ContinuousFunctionPlot<Y, X, 2> :
  public FunctionPlot<Y, X, 2>,
  public Qwt3D::SurfacePlot {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  ContinuousFunctionPlot(const std::string& title, const
    ContinuousFunction<Y, X, 2>& function, const Eigen::Matrix<X, 2, 1>&
    minimum, const Eigen::Matrix<X, 2, 1>& maximum, const X& resolution) throw
    (BadArgumentException<Eigen::Matrix<X, 2, 1> >, BadArgumentException<X>);
  /// Copy constructor
  ContinuousFunctionPlot(const ContinuousFunctionPlot<Y, X, 2>& other);
  /// Assignment operator
  ContinuousFunctionPlot<Y, X, 2>& operator =
    (const ContinuousFunctionPlot<Y, X, 2>& other);
  /// Destructor
  virtual ~ContinuousFunctionPlot();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the plot's resolution
  void setResolution(const X& resolution);
  /// Returns the plot's resolution
  const X& getResolution() const;
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Data on to be plotted
  double **mData;
  /// Resolution on the x/y-axis
  X mResolution;
  /** @}
    */

};

#include "visualization/ContinuousFunctionPlot2v.tpp"

#endif // CONTINUOUSFUNCTIONPLOT2V_H
