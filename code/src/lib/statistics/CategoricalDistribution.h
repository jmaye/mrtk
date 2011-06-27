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

/** \file CategoricalDistribution.h
    \brief This file defines the CategoricalDistribution class, which
           represents a categorical distribution
  */

#ifndef CATEGORICALDISTRIBUTION_H
#define CATEGORICALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"

#include <Eigen/Core>

#include <iosfwd>

#include <stdint.h>

/** The CategoricalDistribution class represents a categorical distribution,
    i.e., the discrete distribution of a random event that can take one out of K
    values
    \brief Categorical distribution
  */
class CategoricalDistribution {
  friend std::ostream& operator << (std::ostream& stream, const CategoricalDistribution& obj);
  friend std::istream& operator >> (std::istream& stream, CategoricalDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const CategoricalDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, CategoricalDistribution& obj);

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
  /// Events probabilities
  Eigen::VectorXd mEventProbabilitiesVector;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  CategoricalDistribution(const Eigen::VectorXd& eventProbabilitiesVector);
  /// Copy constructor
  CategoricalDistribution(const CategoricalDistribution& other);
  //// Assignment operator
  CategoricalDistribution& operator = (const CategoricalDistribution& other);
  /// Destructor
  ~CategoricalDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the event probabilities
  void setEventProbabilities(const Eigen::VectorXd& eventProbabilitiesVector)
    throw (OutOfBoundException);
  /// Returns the event probabilities
  const Eigen::VectorXd& getEventProbabilities() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability mass function at a point
  double pmf(uint32_t u32Event) const throw (OutOfBoundException);
  /// Returns the log-probability mass function at a point
  double logpmf(uint32_t u32Event) const throw (InvalidOperationException);
  /// Returns a sample from the distribution
  uint32_t sample() const;
  /** @}
    */

protected:

};

#endif // CATEGORICALDISTRIBUTION_H
