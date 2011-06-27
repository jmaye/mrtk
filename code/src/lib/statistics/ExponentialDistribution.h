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

/** \file ExponentialDistribution.h
    \brief This file defines the ExponentialDistribution class, which represents
           an exponential distribution
  */

#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

/** The ExponentialDistribution class represents an exponential distribution,
    i.e., a continuous distribution that models the time between events in a
    Poisson process, or the time for a continuous process to change state. The
    events appear at a constant average rate.
    \brief Exponential distribution
  */
class ExponentialDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const ExponentialDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    ExponentialDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const ExponentialDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    ExponentialDistribution& obj);

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
  /// Rate
  double mf64Lambda;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameter
  ExponentialDistribution(double f64Lambda);
  /// Copy constructor
  ExponentialDistribution(const ExponentialDistribution& other);
  //// Assignment operator
  ExponentialDistribution& operator = (const ExponentialDistribution& other);
  /// Destructor
  ~ExponentialDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the event rate
  void setLambda(double f64Lambda) throw (OutOfBoundException);
  /// Returns the event rate
  double getLambda() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability density function at a point
  double pdf(double f64X) const;
  /// Returns the log-probability density function at a point
  double logpdf(double f64X) const throw (OutOfBoundException);
  /// Returns the cumulative density function at a point
  double cdf(double f64X) const;
  /// Returns a sample from the distribution
  double sample() const;
  /// Returns the KL-divergence with another distribution
  double KLDivergence(const ExponentialDistribution& other) const;
  /** @}
    */

protected:

};

#endif // EXPONENTIALDISTRIBUTION_H
