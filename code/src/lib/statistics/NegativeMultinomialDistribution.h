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

/** \file NegativeMultinomialDistribution.h
    \brief This file defines the NegativeMultinomialDistribution class, which
           represents a negative multinomial distribution
  */

#ifndef NEGATIVEMULTINOMIALDISTRIBUTION_H
#define NEGATIVEMULTINOMIALDISTRIBUTION_H

#include "statistics/MultinomialDistribution.h"

/** The NegativeMultinomialDistribution class represents a negative multinomial
    distribution, i.e., the discrete distribution that models the number of
    successes in a sequence of categorical trials before a specified
    (non-random) number of failures occurs.
    \brief Negative multinomial distribution
  */
template <size_t M> class NegativeMultinomialDistribution :
  public MultinomialDistribution<M> {
public:
  /** \name Traits
    @{
    */
  /// Support for the N - 1 simplex
  template <size_t N, size_t D = 0> struct Traits {
  public:
    /// Returns the probability mass function at a point
    static double pmf(const NegativeMultinomialDistribution<N>& distribution,
      const Eigen::Matrix<size_t, N - 1, 1>& value);
    /// Returns the log-probability mass function at a point
    static double logpmf(const NegativeMultinomialDistribution<N>& distribution,
      const Eigen::Matrix<size_t, N - 1, 1>& value);
  };
  /// Support for N = 2
  template <size_t D> struct Traits<2, D> {
  public:
    /// Returns the probability mass function at a point
    static double pmf(const NegativeMultinomialDistribution<2>& distribution,
      const size_t& value);
    /// Returns the log-probability mass function at a point
    static double logpmf(const NegativeMultinomialDistribution<2>& distribution,
      const size_t& value);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  NegativeMultinomialDistribution(size_t numTrials = 1, const
    Eigen::Matrix<double, M, 1>& successProbabilities =
    Eigen::Matrix<double, M, 1>::Constant(1.0 / M));
  /// Copy constructor
  NegativeMultinomialDistribution(const NegativeMultinomialDistribution& other);
  /// Assignment operator
  NegativeMultinomialDistribution& operator =
    (const NegativeMultinomialDistribution& other);
  /// Destructor
  virtual ~NegativeMultinomialDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the probability mass function at a point
  virtual double pmf(const Eigen::Matrix<size_t, M, 1>& value) const;
  /// Returns the probability mass function at a point
  virtual double pmf(const typename
    DiscreteDistribution<size_t, M - 1>::Domain& value) const;
  /// Returns the log-probability mass function at a point
  double logpmf(const Eigen::Matrix<size_t, M, 1>& value) const
    throw (BadArgumentException<Eigen::Matrix<size_t, M, 1> >);
  /// Returns the log-probability mass function at a point
  double logpmf(const typename DiscreteDistribution<size_t, M - 1>::Domain&
    value) const;
  /// Access a sample drawn from the distribution
  virtual Eigen::Matrix<size_t, M, 1> getSample() const;
  /** @}
    */

protected:

};

#include "statistics/NegativeMultinomialDistribution.tpp"

#endif // NEGATIVEMULTINOMIALDISTRIBUTION_H
