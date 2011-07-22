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

/** \file Histogram2v.h
    \brief This file contains the definition of a bivariate histogram
  */

#ifndef HISTOGRAM2V_H
#define HISTOGRAM2V_H

#include "base/Serializable.h"

template <typename T, size_t M> class Histogram;

/** The Histogram2v class defines bivariate histograms
    \brief 2-v histogram
  */
template <typename T> class Histogram<T, 2> :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs histogram from parameters
  Histogram();
  /// Copy constructor
  Histogram(const Histogram<T, 2>& other);
  /// Assignment operator
  Histogram<T, 2>& operator = (const Histogram<T, 2>& other);
  /// Destructor
  virtual ~Histogram();
  /** @}
    */

  /** \name Accessors
    @{
    */
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
  /** @}
    */

};

#include "statistics/Histogram2v.tpp"

#endif // HISTOGRAM2V_H
