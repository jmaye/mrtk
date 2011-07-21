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

/** \file FunctionPlot.h
    \brief This file is an interface for plotting any kind of functions
  */

#ifndef FUNCTIONPLOT_H
#define FUNCTIONPLOT_H

#include <string>

/** The FunctionPlot class is an interface for plotting any kind of functions.
    \brief Function plotting interface
  */
template <typename Y, typename X> class FunctionPlot {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  FunctionPlot(const std::string& title, const X& minimum, const X& maximum);
  /// Copy constructor
  FunctionPlot(const FunctionPlot<Y, X>& other);
  /// Assignment operator
  FunctionPlot<Y, X>& operator = (const FunctionPlot<Y, X>& other);
  /// Destructor
  virtual ~FunctionPlot();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the plot's title
  void setTitle(const std::string& title);
  /// Returns the plot's title
  const std::string& getTitle() const;
  /// Sets the plot's minimum
  void setMinimum(const X& minimum);
  /// Returns the plot's minimum
  const X& getMinimum() const;
  /// Sets the plot's maximum
  void setMaximum(const X& maximum);
  /// Returns the plot's maximum
  const X& getMaximum() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Show the plot
  virtual void show() = 0;
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Title of the graph
  std::string mTitle;
  /// Minimum value on the x-axis
  X mMinimum;
  /// Maximum value on the x-axis
  X mMaximum;
  /** @}
    */

};

#include "visualization/FunctionPlot.tpp"

#endif // FUNCTIONPLOT_H
