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

/** \file NormalDistribution.h
    \brief This file defines the NormalDistribution class, which represents a
           normal distribution
  */

#ifndef NORMALDISTRIBUTION_H
#define NORMALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"
#include "statistics/ContinuousDistribution.h"

#include <iosfwd>

/** The NormalDistribution class represents a normal distribution
    \brief Normal distribution
  */
class NormalDistribution :
  public ContinuousDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const NormalDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    NormalDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const NormalDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    NormalDistribution& obj);

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
  /// Mean of the normal distribution
  double mf64Mean;
  /// Variance of the normal distribution
  double mf64Variance;
  /// Precision of the normal distribution
  double mf64Precision;
  /// Standard deviation of the normal distribution
  double mf64StandardDeviation;
  /// Normalizer of the normal distribution
  double mf64Normalizer;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs a normal distribution from the parameters
  NormalDistribution(double f64Mean = 0.0, double f64Variance = 1.0);
  /// Copy constructor
  NormalDistribution(const NormalDistribution& other);
  /// Assignment operator
  NormalDistribution& operator = (const NormalDistribution& other);
  /// Destructor
  ~NormalDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the mean of the distribution
  void setMean(double f64Mean);
  /// Returns the mean of the distribution
  double getMean() const;
  /// Sets the variance of the distribution
  void setVariance(double f64Variance) throw (OutOfBoundException);
  /// Returns the variance of the distribution
  double getVariance() const;
  /// Returns the precision of the distribution
  double getPrecision() const;
  /// Returns the standard deviation of the distribution
  double getStandardDeviation() const;
  /// Returns the normalizer of the distribution
  double getNormalizer() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability density function at a point
  double pdf(double f64X) const;
  /// Returns the log-probability density function at a point
  double logpdf(double f64X) const;
  /// Returns the cumulative density function at a point
  double cdf(double f64X) const;
  /// Returns a sample of the distribution
  double sample() const;
  /// Returns the KL-divergence with another distribution
  double KLDivergence(const NormalDistribution& other) const;
  /// Returns the Mahalanobis distance from a point
  double mahalanobisDistance(double f64Value) const;
  /** @}
    */

protected:

};

#endif // NORMALDISTRIBUTION_H
