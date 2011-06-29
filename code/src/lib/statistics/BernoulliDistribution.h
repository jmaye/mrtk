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

#include "statistics/DiscreteDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"


/** The class BernoulliDistribution represents a Bernoulli distribution, i.e.,
    the discrete distribution of a random event with success or failure.
    \brief Bernoulli distribution
  */
class BernoulliDistribution :
  public DiscreteDistribution<size_t>,
  public SampleDistribution<size_t>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameter
  BernoulliDistribution(double successProbability = 0.5);
  /// Copy constructor
  BernoulliDistribution(const BernoulliDistribution& other);
  //// Assignment operator
  BernoulliDistribution& operator = (const BernoulliDistribution& other);
  /// Destructor
  virtual ~BernoulliDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the success probability
  void setSuccessProbability(double successProbability)
    throw (BadArgumentException<double>);
  /// Returns the success probability
  double getSuccessProbability() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability mass function at a point
  virtual double pmf(const size_t& value) const
    throw (BadArgumentException<size_t>);
  /// Access a sample drawn from the distribution
  virtual size_t getSample() const;
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

  /** \name Private members
    @{
    */
  /// Success probability
  double mSuccessProbability;
  /** @}
    */

};

#include "statistics/BernoulliDistribution.tpp"

#endif // BERNOULLIDISTRIBUTION_H
