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

/** \file NegativeBinomialDistribution.h
    \brief This file defines the NegativeBinomialDistribution class, which
           represents a negative binomial distribution
  */

#ifndef NEGATIVEBINOMIALDISTRIBUTION_H
#define NEGATIVEBINOMIALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

#include <stdint.h>

/** The NegativeBinomialDistribution class represents a negative binomial
    distribution, i.e. a discrete distribution that models the number of
    successes in a sequence of Bernoulli trials before a specified (non-random)
    number r of failures occurs
    \brief Negative binomial distribution
  */
class NegativeBinomialDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const NegativeBinomialDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    NegativeBinomialDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const NegativeBinomialDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    NegativeBinomialDistribution& obj);

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
  /// Number of failures until the experiment is stopped
  uint32_t mu32FailuresNbr;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  NegativeBinomialDistribution(uint32_t u32FailuresNbr, double f64P);
  /// Copy constructor
  NegativeBinomialDistribution(const NegativeBinomialDistribution& other);
  //// Assignment operator
  NegativeBinomialDistribution& operator = (const NegativeBinomialDistribution&
    other);
  /// Destructor
  ~NegativeBinomialDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the success probability
  void setP(double f64P) throw (OutOfBoundException);
  /// Returns the success probability
  double getP() const;
  /// Sets the number of failures
  void setFailuresNbr(uint32_t u32FailuresNbr) throw (OutOfBoundException);
  /// Returns the number of failures
  uint32_t getFailuresNbr() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability mass function at a point
  double pmf(uint32_t u32SuccNbr) const;
  /// Returns the log-probability mass function at a point
  double logpmf(uint32_t u32SuccNbr) const;
  /// Returns a sample from the distribution
  uint32_t sample() const;
  /** @}
    */

protected:

};

#endif // NEGATIVEBINOMIALDISTRIBUTION_H
