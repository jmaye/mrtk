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

/** \file DCMDistribution.h
    \brief This file defines the DCMDistribution class, which represents
           a Dirichlet Compound Multinomial distribution
  */

#ifndef DCMDISTRIBUTION_H
#define DCMDISTRIBUTION_H

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "exceptions/BadArgumentException.h"
#include "base/Serializable.h"

/** The DCMDistribution class represents a Dirichlet Compound Multinomial
    distribution.
    \brief Dirichlet Compound Multinomial distribution
  */
template <size_t M> class DCMDistribution :
  public ContinuousDistribution<double, M>,
  public ContinuousDistribution<double, M - 1>,
  public SampleDistribution<Eigen::Matrix<double, M, 1> >,
  public virtual Serializable {
public:
  /** \name Traits
    @{
    */
  /// Support for the N - 1 simplex
  template <size_t N, size_t D = 0> struct Traits {
  public:
    /// Access the probability density function at the given value
    static double pdf(const DCMDistribution<N>& distribution,
      const Eigen::Matrix<double, N - 1, 1>& value);
    /// Access the log-probability density function at the given value
    static double logpdf(const DCMDistribution<N>& distribution,
      const Eigen::Matrix<double, N - 1, 1>& value);
  };
  /// Support for N = 2
  template <size_t D> struct Traits<2, D> {
  public:
    /// Access the probability density function at the given value
    static double pdf(const DCMDistribution<2>& distribution,
      const double& value);
    /// Access the log-probability density function at the given value
    static double logpdf(const DCMDistribution<2>& distribution,
      const double& value);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  DCMDistribution(const Eigen::Matrix<double, M, 1>& alpha =
    Eigen::Matrix<double, M, 1>::Ones());
  /// Copy constructor
  DCMDistribution(const DCMDistribution<M>& other);
  /// Assignment operator
  DCMDistribution& operator = (const DCMDistribution<M>& other);
  /// Destructor
  virtual ~DCMDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the alpha parameter
  void setAlpha(const Eigen::Matrix<double, M, 1>& alpha)
    throw (BadArgumentException<Eigen::Matrix<double, M, 1> >);
  /// Returns the alpha parameter
  const Eigen::Matrix<double, M, 1>& getAlpha() const;
  /// Returns the normalizer
  double getNormalizer() const;
  /// Returns the mean of the distribution
  Eigen::Matrix<double, M, 1> getMean() const;
  /// Returns the covariance of the distribution
  Eigen::Matrix<double, M, M> getCovariance() const;
  /// Access the probability density function at the given value
  virtual double pdf(const Eigen::Matrix<double, M, 1>& value) const;
  /// Access the probability density function at the given value
  virtual double pdf(const typename
    ContinuousDistribution<double, M - 1>::Domain& value) const;
  /// Access the log-probablity density function at the given value
  double logpdf(const Eigen::Matrix<double, M, 1>& value) const
    throw (BadArgumentException<Eigen::Matrix<double, M, 1> >);
  /// Access the log-probablity density function at the given value
  double logpdf(const typename
    ContinuousDistribution<double, M - 1>::Domain& value) const;
  /// Access a sample drawn from the distribution
  virtual Eigen::Matrix<double, M, 1> getSample() const;
  /** @}
    */

  using ContinuousDistribution<double, M>::operator();
  using ContinuousDistribution<double, M - 1>::operator();

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
  /// Pseudo-counts
  Eigen::Matrix<double, M, 1> mAlpha;
  /// Normalizer
  double mf64Normalizer;
  /** @}
    */

};

#include "statistics/DCMDistribution.tpp"

#endif // DCMDISTRIBUTION_H
