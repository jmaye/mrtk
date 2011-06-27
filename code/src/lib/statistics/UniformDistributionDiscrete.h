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

/** \file UniformDistributionDiscrete.h
    \brief This file defines the UniformDistributionDiscrete class, which
           represents a discrete uniform distribution
  */

#ifndef UNIFORMDISTRIBUTIONDISCRETE_H
#define UNIFORMDISTRIBUTIONDISCRETE_H

#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"

#include <iosfwd>

#include <stdint.h>

/** The UniformDistributionDiscrete class represents a discrete uniform
    distribution.
    \brief Discrete uniform distribution
  */
class UniformDistributionDiscrete {
  friend std::ostream& operator << (std::ostream& stream,
    const UniformDistributionDiscrete& obj);
  friend std::istream& operator >> (std::istream& stream,
    UniformDistributionDiscrete& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniformDistributionDiscrete& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    UniformDistributionDiscrete& obj);

  /** \name Streaming methods
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
  /// Minimum support of the distribution
  int32_t mi32MinSupport;
  /// Maximum support of the distribution
  int32_t mi32MaxSupport;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs a distribution from the parameters
  UniformDistributionDiscrete(int32_t i32MinSupport, int32_t i32MaxSupport)
    throw (OutOfBoundException);
  /// Copy constructor
  UniformDistributionDiscrete(const UniformDistributionDiscrete& other);
  /// Assignment operator
  UniformDistributionDiscrete& operator = (const UniformDistributionDiscrete&
    other);
  /// Destructor
  ~UniformDistributionDiscrete();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the minimum support for the distribution
  void setMinSupport(int32_t i32Value) throw (OutOfBoundException);
  /// Returns the minimum support for the distribution
  int32_t getMinSupport() const;
  /// Sets the maximum support for the distribution
  void setMaxSupport(int32_t i32Value) throw (OutOfBoundException);
  /// Returns the maximum support for the distribution
  int32_t getMaxSupport() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability mass function at a point
  double pmf(int32_t i32X) const;
  /// Returns the log-probability mass function at a point
  double logpmf(int32_t i32X) const throw (InvalidOperationException);
  /// Returns a sample from the distribution
  int32_t sample() const;
  /** @}
    */

protected:

};

#include "statistics/UniformDistributionDiscrete.tpp"

#endif // UNIFORMDISTRIBUTIONDISCRETE_H
