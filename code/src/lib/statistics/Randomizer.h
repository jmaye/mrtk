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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file Randomizer.h
    \brief This file defines the Randomizer class, which implements random
           sampling from several distributions
  */

#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"
#include "utils/SizeTSupport.h"

/** The Randomizer class implements random sampling from several distributions
    \brief Random sampling from distributions
  */
template <typename T = double, size_t M = 1> class Randomizer :
  public virtual Serializable {
public:
  /** \name Traits
    @{
    */
  /// Rounding support for all integer types
  template <typename U, size_t D = 0> struct Traits {
  public:
    /// Round function
    static U round(double value);
  };
  /// Rounding support for float type
  template <size_t D> struct Traits<float, D> {
  public:
    /// Round function
    static float round(float value);
  };
  /// Rounding support for double type
  template <size_t D> struct Traits<double, D> {
  public:
    /// Round function
    static double round(double value);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs randomizer from seed
  Randomizer(const T& seed = getSeed());
  /// Copy constructor
  Randomizer(const Randomizer<T, M>& other);
  /// Assignment operator
  Randomizer<T, M>& operator = (const Randomizer<T, M>& other);
  /// Destructor
  virtual ~Randomizer();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the seed of the random sampler
  void setSeed(const T& seed);
  /// Returns the seed of the random sampler
  static T getSeed();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a sample from a uniform distribution within the specified support
  T sampleUniform(const T& minSupport = T(0), const T& maxSupport = T(1)) const
    throw (BadArgumentException<T>);
  /// Returns a sample from a normal distribution
  T sampleNormal(const T& mean = T(0), const T& variance = T(1)) const
    throw (BadArgumentException<T>);
  /// Returns a sample from a categorical distribution
  Eigen::Matrix<size_t, M, 1> sampleCategorical(const
    Eigen::Matrix<double, M, 1>& successProbabilities =
    Eigen::Matrix<double, M, 1>::Constant(1.0 / M))
    const throw (BadArgumentException<Eigen::Matrix<double, M, 1> >);
  /// Returns a sample from a Poisson distribution
  size_t samplePoisson(double rate = 1.0) const
    throw (BadArgumentException<double>);
  /// Returns a sample from a exponential distribution
  double sampleExponential(double rate = 1.0) const
    throw (BadArgumentException<double>);
  /// Returns a sample from a geometric distribution
  size_t sampleGeometric(double successProbability = 0.5) const
    throw (BadArgumentException<double>);
  /// Returns a sample from a gamma distribution
  double sampleGamma(double shape = 1.0, double scale = 1.0) const
    throw (BadArgumentException<double>);
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

  /** \name Protected members
    @{
    */
  /// Seed of the random sampling
  T mSeed;
  /** @}
    */

};

#include "statistics/Randomizer.tpp"

#endif // RANDOMIZER_H
