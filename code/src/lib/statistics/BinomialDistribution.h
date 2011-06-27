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

/** \file BinomialDistribution.h
    \brief This file defines the BinomialDistribution class, which represents a
           binomial distribution
  */

#ifndef BINOMIALDISTRIBUTION_H
#define BINOMIALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

#include <stdint.h>

/** The BinomialDistribution class represents a binomial distribution, i.e., the
    discrete distribution of the number of successes in N independent Bernoulli
    draws, each with the same probability of success p
    \brief Binomial distribution
  */
class BinomialDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const BinomialDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    BinomialDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const BinomialDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    BinomialDistribution& obj);

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
  /// Number of trials
  uint32_t mu32TrialsNbr;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameter
  BinomialDistribution(uint32_t u32TrialsNbr, double f64P);
  /// Copy constructor
  BinomialDistribution(const BinomialDistribution& other);
  //// Assignment operator
  BinomialDistribution& operator = (const BinomialDistribution& other);
  /// Destructor
  ~BinomialDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the success probability
  void setP(double f64P) throw (OutOfBoundException);
  /// Returns the success probability
  double getP() const;
  /// Sets the number of trials
  void setTrialsNbr(uint32_t u32TrialsNbr) throw (OutOfBoundException);
  /// Returns the number of trials
  uint32_t getTrialsNbr() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability mass function at a point
  double pmf(uint32_t u32SuccNbr) const;
  /// Returns the log-probability mass at a point
  double logpmf(uint32_t u32SuccNbr) const throw (OutOfBoundException);
  /// Returns a sample from the distribution
  uint32_t sample() const;
  /** @}
    */

protected:

};

#include "statistics/BinomialDistribution.tpp"

#endif // BINOMIALDISTRIBUTION_H
