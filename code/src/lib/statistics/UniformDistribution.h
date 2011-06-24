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

/** \file UniformDistribution.h
    \brief This file defines the UniformDistribution class, which represents a
           uniform distribution
  */

#ifndef UNIFORMDISTRIBUTION_H
#define UNIFORMDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"
#include "statistics/ContinuousDistribution.h"

#include <iosfwd>

/** The UniformDistribution class represents a uniform distribution
    \brief Uniform distribution
  */
class UniformDistribution :
  public ContinuousDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const UniformDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    UniformDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniformDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    UniformDistribution& obj);

  /** \name Streaming methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Streaming methods
    @{
    */
  /// Minimum support of the distribution
  double mf64MinSupport;
  /// Maximum support of the distribution
  double mf64MaxSupport;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs a uniform distribution from parameters
  UniformDistribution(double f64MinSupport = 0.0, double f64MaxSupport = 1.0)
    throw (OutOfBoundException);
  /// Copy constructor
  UniformDistribution(const UniformDistribution& other);
  /// Assignment operator
  UniformDistribution& operator = (const UniformDistribution& other);
  /// Destructor
  ~UniformDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the minimum support of the distribution
  void setMinSupport(double f64Value) throw (OutOfBoundException);
  /// Returns the minimum support of the distribution
  double getMinSupport() const;
  /// Sets the maximum support of the distribution
  void setMaxSupport(double f64Value) throw (OutOfBoundException);
  /// Returns the maximum support of the distribution
  double getMaxSupport() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns probability density function of a point
  double pdf(double f64X) const;
  /// Returns log-probability density function of a point
  double logpdf(double f64X) const throw (InvalidOperationException);
  /// Returns a sample from the distribution
  double sample() const;
  /** @}
    */

protected:

};

#endif // UNIFORMDISTRIBUTION_H
