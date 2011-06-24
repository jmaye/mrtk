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

/** \file MultinomialDistribution.h
    \brief This file defines the MultinomialDistribution class, which represents
           a multinomial distribution
  */

#ifndef MULTINOMIALDISTRIBUTION_H
#define MULTINOMIALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"
#include "statistics/MvDiscreteDistribution.h"

#include <Eigen/Core>

#include <iosfwd>
#include <vector>

#include <stdint.h>

/** The MultinomialDistribution class represents a multinomial distribution,
    i.e., the discrete distribution of N independent categorical distribution
    draws
    \brief Multinomial distribution
  */
class MultinomialDistribution :
  public MvDiscreteDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const MultinomialDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    MultinomialDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const MultinomialDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    MultinomialDistribution& obj);

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
  /// Number of trials
  uint32_t mu32TrialsNbr;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  MultinomialDistribution(uint32_t u32TrialsNbr,
    const Eigen::VectorXd& eventProbabilitiesVector);
  /// Copy constructor
  MultinomialDistribution(const MultinomialDistribution& other);
  //// Assignment operator
  MultinomialDistribution& operator = (const MultinomialDistribution& other);
  /// Destructor
  ~MultinomialDistribution();
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
  double pmf(const Eigen::VectorXi& xVector) const;
  /// Returns the log-probability mass function at a point
  double logpmf(const Eigen::VectorXi& xVector) const
    throw (OutOfBoundException);
  /// Returns a sample from the distribution
  const Eigen::VectorXi sample() const;
  /** @}
    */

protected:

};

#endif // MULTINOMIALDISTRIBUTION_H
