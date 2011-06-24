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

#include "misc/Timestamp.h"
#include "exceptions/OutOfBoundException.h"
#include "statistics/MvNormalDistribution.h"

#include <Eigen/Core>

#include <iosfwd>

#include <stdint.h>

/** The Randomizer class implements random sampling from several distributions
    \brief Random sampling from distributions
  */
class Randomizer {
  friend std::ostream& operator << (std::ostream& stream,
    const Randomizer& obj);
  friend std::istream& operator >> (std::istream& stream, Randomizer& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Randomizer& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Randomizer& obj);

  /** \name Streaming methods
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
  /// Seed of the random sampling
  double mf64Seed;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  Randomizer(double f64Seed = Timestamp::now());
  /// Copy constructor
  Randomizer(const Randomizer& other);
  /// Assignment operator
  Randomizer& operator = (const Randomizer& other);
  /// Destructor
  ~Randomizer();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the seed of the random sampler
  void setSeed(double f64Seed);
  /// Returns the seed of the random sampler
  double getSeed() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a sample from a uniform distribution
  double sampleUniform(double f64MinSupport = 0.0, double f64MaxSupport = 1.0)
    const throw (OutOfBoundException);
  /// Returns a sample from a discrete uniform distribution
  int32_t sampleUniform(int32_t i32MinSupport, int32_t i32MaxSupport)
    const throw (OutOfBoundException);
  /// Returns a sample from a normal distribution
  double sampleNormal(double f64Mean = 0.0, double f64Variance = 1.0) const
    throw (OutOfBoundException);
  /// Returns a sample from a multivariate normal distribution
  const Eigen::VectorXd sampleNormal(const Eigen::VectorXd& meanVector,
    const Eigen::MatrixXd& covarianceMatrix) const
    throw (OutOfBoundException);
  /// Returns a sample from a multivariate normal distribution
  const Eigen::VectorXd sampleNormal(const MvNormalDistribution& dist) const;
  /// Returns a sample from the Bernoulli distribution
  bool sampleBernoulli(double f64P) const throw (OutOfBoundException);
  /// Returns a sample from the categorical distribution
  uint32_t sampleCategorical(const Eigen::VectorXd& eventProbabilitiesVector)
    const throw (OutOfBoundException);
  /// Returns a sample from the Poisson distribution
  uint32_t samplePoisson(double f64Lambda) const throw (OutOfBoundException);
  /// Returns a sample from the exponential distribution
  double sampleExponential(double f64Lambda) const
    throw (OutOfBoundException);
  /// Returns a sample from the geometric distribution
  uint32_t sampleGeometric(double f64P) const throw (OutOfBoundException);
  /// Returns a sample from the gamma distribution
  double sampleGamma(double f64K, double f64Theta) const
    throw (OutOfBoundException);
  /// Returns a sample from the beta distribution
  double sampleBeta(double f64Alpha, double f64Beta) const
    throw (OutOfBoundException);
  /** @}
    */

protected:

};

#endif // RANDOMIZER_H
