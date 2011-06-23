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

/** \file PoissonDistribution.h
    \brief This file defines the PoissonDistribution class, which represents a
           Poisson distribution
  */

#ifndef POISSONDISTRIBUTION_H
#define POISSONDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

#include <stdint.h>

/** The PoissonDistribution class represents a Poisson distribution, i.e., a
    discrete distribution that models the probability of a given number of
    events occurring in a fixed interval of time and/or space with a known
    average rate
    \brief Poisson distribution
  */
class PoissonDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const PoissonDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    PoissonDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const PoissonDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    PoissonDistribution& obj);

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
  /// Event rate
  double mf64Lambda;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameter
  PoissonDistribution(double f64Lambda);
  /// Copy constructor
  PoissonDistribution(const PoissonDistribution& other);
  //// Assignment operator
  PoissonDistribution& operator = (const PoissonDistribution& other);
  /// Destructor
  ~PoissonDistribution();
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
  /// Returns the probability mass function at a point
  double pmf(uint32_t u32X) const;
  /// Returns the log-probability mass function at a point
  double logpmf(uint32_t u32X) const;
  /// Returns a sample from the distribution
  uint32_t sample() const;
  /** @}
    */

protected:

};

#endif // POISSONDISTRIBUTION_H
