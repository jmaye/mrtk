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

/** \file BetaDistribution.h
    \brief This file defines the BetaDistribution class, which represents
           a beta distribution
  */

#ifndef BETADISTRIBUTION_H
#define BETADISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

/** The BetaDistribution class represents a beta distribution,
    i.e., a continuous distribution that is a conjugate prior to the binomial or
    Bernoulli distribution
    \brief Beta distribution
  */
class BetaDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const BetaDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    BetaDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const BetaDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    BetaDistribution& obj);

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
  /// mf64Alpha - 1 corresponds to success observations
  double mf64Alpha;
  /// mf64Beta - 1 corresponds to failure observations
  double mf64Beta;
  /// Normalizer
  double mf64Normalizer;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  BetaDistribution(double f64Alpha, double f64Beta);
  /// Copy constructor
  BetaDistribution(const BetaDistribution& other);
  //// Assignment operator
  BetaDistribution& operator = (const BetaDistribution& other);
  /// Destructor
  ~BetaDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of successes
  void setAlpha(double f64Alpha) throw (OutOfBoundException);
  /// Returns the number of successes
  double getAlpha() const;
  /// Sets the number of failures
  void setBeta(double f64Beta) throw (OutOfBoundException);
  /// Returns the number of failures
  double getBeta() const;
  /// Returns the normalizer
  double getNormalizer() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability density function at a point
  double pdf(double f64X) const;
  /// Returns the log-probability density function at a point
  double logpdf(double f64X) const throw (OutOfBoundException);
  /// Returns a sample from the distribution
  double sample() const;
  /** @}
    */

protected:

};

#endif // BETADISTRIBUTION_H
