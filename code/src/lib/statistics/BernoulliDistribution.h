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

/** \file BernoulliDistribution.h
    \brief This file defines the BernoulliDistribution class, which represents a
           Bernoulli distribution
  */

#ifndef BERNOULLIDISTRIBUTION_H
#define BERNOULLIDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"

#include <iosfwd>

/** The class BernoulliDistribution represents a Bernoulli distribution, i.e.,
    the discrete distribution of a random event with success or failure
    \brief Bernoulli distribution
  */
class BernoulliDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const BernoulliDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    BernoulliDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const BernoulliDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    BernoulliDistribution& obj);

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
  /// Constructs the distribution from the parameter
  BernoulliDistribution(double f64P);
  /// Copy constructor
  BernoulliDistribution(const BernoulliDistribution& other);
  //// Assignment operator
  BernoulliDistribution& operator = (const BernoulliDistribution& other);
  /// Destructor
  ~BernoulliDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the value for p
  void setP(double f64P) throw (OutOfBoundException);
  /// Returns the value of p
  double getP() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability mass function at a point
  double pmf(bool bX) const;
  /// Returns the log-probability mass function at a point
  double logpmf(bool bX) const throw (InvalidOperationException);
  /// Returns a sample from the distribution
  bool sample() const;
  /** @}
    */

protected:

};

#include "statistics/BernoulliDistribution.tpp"

#endif // BERNOULLIDISTRIBUTION_H
