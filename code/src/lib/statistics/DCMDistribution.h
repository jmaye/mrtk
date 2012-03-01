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

#include "statistics/DiscreteDistribution.h"
#include "statistics/SampleDistribution.h"
#include "statistics/DirichletDistribution.h"
#include "exceptions/BadArgumentException.h"
#include "base/Serializable.h"

/** The DCMDistribution class represents a Dirichlet Compound Multinomial
    distribution, which is the predictive distribution of a multinomial random
    variable.
    \brief Dirichlet Compound Multinomial distribution
  */
template <size_t M> class DCMDistribution :
  public DiscreteDistribution<int, M>,
  public DiscreteDistribution<int, M - 1>,
  public SampleDistribution<Eigen::Matrix<int, M, 1> >,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Distribution type
  typedef DiscreteDistribution<int, M> DistributionType;
  /// Random variable type
  typedef typename DistributionType::RandomVariable RandomVariable;
  /// Mean type
  typedef typename DistributionType::Mean Mean;
  /// Covariance type
  typedef typename DistributionType::Covariance Covariance;
  /** @}
    */

  /** \name Traits
    @{
    */
  /// Support for the N - 1 simplex
  template <size_t N, size_t D = 0> struct Traits {
  public:
    /// Access the probability mass function at the given value
    static double pmf(const DCMDistribution<N>& distribution, const
      Eigen::Matrix<int, N - 1, 1>& value);
    /// Access the log-probability mass function at the given value
    static double logpmf(const DCMDistribution<N>& distribution, const
      Eigen::Matrix<int, N - 1, 1>& value);
  };
  /// Support for N = 2
  template <size_t D> struct Traits<2, D> {
  public:
    /// Access the probability mass function at the given value
    static double pmf(const DCMDistribution<2>& distribution, const int&
      value);
    /// Access the log-probability mass function at the given value
    static double logpmf(const DCMDistribution<2>& distribution, const int&
      value);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  DCMDistribution(size_t numTrials = 1, const Eigen::Matrix<double, M, 1>&
    alpha = Eigen::Matrix<double, M, 1>::Ones());
  /// Copy constructor
  DCMDistribution(const DCMDistribution& other);
  /// Assignment operator
  DCMDistribution& operator = (const DCMDistribution& other);
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
  /// Sets the number of trials
  void setNumTrials(size_t numTrials) throw (BadArgumentException<size_t>);
  /// Returns the number of trials
  size_t getNumTrials() const;
  /// Returns the mean of the distribution
  Mean getMean() const;
  /// Returns the covariance of the distribution
  Covariance getCovariance() const;
  /// Access the probability mass function at the given value
  virtual double pmf(const RandomVariable& value) const;
  /// Access the probability mass function at the given value
  virtual double pmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const;
  /// Access the log-probablity mass function at the given value
  double logpmf(const RandomVariable& value) const
    throw (BadArgumentException<RandomVariable>);
  /// Access the log-probablity mass function at the given value
  double logpmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const;
  /// Access a sample drawn from the distribution
  virtual RandomVariable getSample() const;
  /** @}
    */

  using DiscreteDistribution<int, M>::operator();
  using DiscreteDistribution<int, M - 1>::operator();

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
  /// Number of trials
  size_t mNumTrials;
  /// Dirichlet distribution for speeding up sampling
  DirichletDistribution<M> mDirDist;
  /** @}
    */

};

#include "statistics/DCMDistribution.tpp"

#endif // DCMDISTRIBUTION_H
