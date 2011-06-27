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

/** \file GeometricDistribution.h
    \brief This file defines the GeometricDistribution class, which represents a
           geometric distribution
  */

#ifndef GEOMETRICDISTRIBUTION_H
#define GEOMETRICDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

#include <stdint.h>

/** The GeometricDistribution class represents a geometric distribution, i.e.,
    a discrete distribution which models the number of Bernoulli trial before
    a success occurs, or the number of Bernoulli trials before a discrete
    process changes state.
    \brief Geometric distribution
  */
class GeometricDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const GeometricDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    GeometricDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const GeometricDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    GeometricDistribution& obj);

  /** \name Stream methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Private members
    @{
    */
  /// Success probability
  double mf64P;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameter
  GeometricDistribution(double f64P);
  /// Copy constructor
  GeometricDistribution(const GeometricDistribution& other);
  //// Assignment operator
  GeometricDistribution& operator = (const GeometricDistribution& other);
  /// Destructor
  ~GeometricDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the success probability
  void setP(double f64P) throw (OutOfBoundException);
  /// Returns the success probability
  double getP() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability mass function at a point
  double pmf(uint32_t u32X) const;
  /// Returns the log-probability mass at a point
  double logpmf(uint32_t u32X) const throw (OutOfBoundException);
  /// Returns a sample from the distribution
  uint32_t sample() const;
  /** @}
    */

protected:

};

#include "statistics/GeometricDistribution.tpp"

#endif // GEOMETRICDISTRIBUTION_H
