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

/** \file Histogram1v.h
    \brief This file contains the definition of an univariate histogram
  */

#ifndef HISTOGRAM1V_H
#define HISTOGRAM1V_H

#include "base/Serializable.h"

#include <Eigen/Core>

template <typename Y, typename X, size_t M> class Histogram;

/** The Histogram1v class defines univariate histograms
    \brief 1-v histogram
  */
template <typename Y, typename X> class Histogram<Y, X, 1> :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs histogram from parameters
  Histogram();
  /// Copy constructor
  Histogram(const Histogram<Y, X, 1>& other);
  /// Assignment operator
  Histogram<Y, X, 1>& operator = (const Histogram<Y, X, 1>& other);
  /// Destructor
  virtual ~Histogram();
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
  /// Normalize the histogram, i.e., it becomes a discrete probability distr.
  void normalize();
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  Eigen::Matrix<double, Eigen::Dynamic, 1> mBins;
  /** @}
    */

};

#include "statistics/Histogram1v.tpp"

#endif // HISTOGRAM1V_H
