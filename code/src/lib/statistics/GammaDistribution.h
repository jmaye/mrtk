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

/** \file GammaDistribution.h
    \brief This file defines the GammaDistribution class, which represents
           a gamma distribution
  */

#ifndef GAMMADISTRIBUTION_H
#define GAMMADISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

/** The GammaDistribution class represents a gamma distribution,
    i.e., a continuous distribution that models waiting times, e.g., the
    waiting time until death. It is also a conjugate prior to the
    Poisson/Exponential/... distributions
    \brief Gamma distribution
  */
class GammaDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const GammaDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    GammaDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const GammaDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    GammaDistribution& obj);

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
  /// Shape parameter
  double mf64K;
  /// Scale parameter
  double mf64Theta;
  /// Normalizer
  double mf64Normalizer;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  GammaDistribution(double f64K, double f64Theta);
  /// Copy constructor
  GammaDistribution(const GammaDistribution& other);
  //// Assignment operator
  GammaDistribution& operator = (const GammaDistribution& other);
  /// Destructor
  ~GammaDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the shape parameter
  void setK(double f64K) throw (OutOfBoundException);
  /// Returns the shape parameter
  double getK() const;
  /// Sets the scale parameter
  void setTheta(double f64Theta) throw (OutOfBoundException);
  /// Returns the scale parameter
  double getTheta() const;
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

#endif // GAMMADISTRIBUTION_H
