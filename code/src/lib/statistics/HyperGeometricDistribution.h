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

/** \file HyperGeometricDistribution.h
    \brief This file defines the HyperGeometricDistribution class, which
           represents an hypergeometric distribution
  */

#ifndef HYPERGEOMETRICDISTRIBUTION_H
#define HYPERGEOMETRICDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

#include <stdint.h>

/** The HyperGeometricDistribution class represents an hyper geometric
    distribution, i.e., a discrete distribution that models the number of
    successes in a sequence of N draws from a finite population without
    replacement
    \brief Hypergeometric distribution
  */
class HyperGeometricDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const HyperGeometricDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    HyperGeometricDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const HyperGeometricDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    HyperGeometricDistribution& obj);

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
  /// Number of balls
  uint32_t mu32N;
  /// Number of white balls
  uint32_t mu32m;
  /// Number of draws
  uint32_t mu32n;
  /// Normalizer
  double mf64Normalizer;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  HyperGeometricDistribution(uint32_t u32N, uint32_t u32m, uint32_t u32n);
  /// Copy constructor
  HyperGeometricDistribution(const HyperGeometricDistribution& other);
  //// Assignment operator
  HyperGeometricDistribution& operator = (const HyperGeometricDistribution&
    other);
  /// Destructor
  ~HyperGeometricDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of balls
  void setN(uint32_t u32N) throw (OutOfBoundException);
  /// Returns the number of balls
  uint32_t getN() const;
  /// Sets the number of white balls
  void setm(uint32_t u32m) throw (OutOfBoundException);
  /// Returns the number of white balls
  uint32_t getm() const;
  /// Sets the number of draws
  void setn(uint32_t u32n) throw (OutOfBoundException);
  /// Returns the number of draws
  uint32_t getn() const;
  /// Returns the normalizer
  double getNormalizer() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability mass function at a point
  double pmf(uint32_t u32X) const;
  /// Returns the log-probability mass function at a point
  double logpmf(uint32_t u32X) const throw (OutOfBoundException);
  /// Returns a sample from the distribution
  uint32_t sample() const;
  /** @}
    */

protected:

};

#endif // HYPERGEOMETRICDISTRIBUTION_H
