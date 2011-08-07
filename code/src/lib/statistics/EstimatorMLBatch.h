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

/** \file EstimatorMLBatch.h
    \brief This file defines the EstimatorMLBatch class, which implements batch
           maximum likelihood estimators for various distributions
  */

#ifndef ESTIMATORMLBATCH_H
#define ESTIMATORMLBATCH_H

#include "statistics/NormalDistribution.h"
#include "statistics/CategoricalDistribution.h"
#include "statistics/MultinomialDistribution.h"
#include "statistics/ExponentialDistribution.h"
#include "statistics/GeometricDistribution.h"
#include "statistics/PoissonDistribution.h"
#include "statistics/LinearRegression.h"

#include <vector>

template <typename D, size_t M = 1> class EstimatorMLBatch;

/** The class EstimatorMLBatch is implemented for univariate normal
    distributions.
    \brief Univariate normal distribution ML estimator
  */
template <> class EstimatorMLBatch<NormalDistribution<1> > {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLBatch();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Estimate the parameters
  static void estimate(NormalDistribution<1>& dist,
    const std::vector<NormalDistribution<1>::VariableType>& points);
  /** @}
    */
};

/** The class EstimatorMLBatch is implemented for multivariate normal
    distributions.
    \brief Multivariate normal distribution ML estimator
  */
template <size_t M> class EstimatorMLBatch<NormalDistribution<M>, M> {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLBatch();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Estimate the parameters
  static void estimate(NormalDistribution<M>& dist,
    const std::vector<typename NormalDistribution<M>::VariableType>& points);
  /** @}
    */
};

/** The class EstimatorMLBatch is implemented for categorical distributions.
    \brief Categorical distribution ML estimator
  */
template <size_t M> class EstimatorMLBatch<CategoricalDistribution<M>, M> {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLBatch();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Estimate the parameters
  static void estimate(CategoricalDistribution<M>& dist,
    const std::vector<Eigen::Matrix<size_t, M, 1> >& points);
  /** @}
    */
};

/** The class EstimatorMLBatch is implemented for multinomial distributions.
    \brief Multinomial distribution ML estimator
  */
template <size_t M> class EstimatorMLBatch<MultinomialDistribution<M>, M> {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLBatch();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Estimate the parameters
  static void estimate(MultinomialDistribution<M>& dist,
    const std::vector<Eigen::Matrix<size_t, M, 1> >& points);
  /** @}
    */
};

/** The class EstimatorMLBatch is implemented for exponential distributions.
    \brief Exponential distribution ML estimator
  */
template <> class EstimatorMLBatch<ExponentialDistribution> {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLBatch();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Estimate the parameters
  static void estimate(ExponentialDistribution& dist,
    const std::vector<ExponentialDistribution::VariableType>& points);
  /** @}
    */
};

/** The class EstimatorMLBatch is implemented for geometric distributions.
    \brief Geometric distribution ML estimator
  */
template <> class EstimatorMLBatch<GeometricDistribution> {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLBatch();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Estimate the parameters
  static void estimate(GeometricDistribution& dist,
    const std::vector<GeometricDistribution::VariableType>& points);
  /** @}
    */
};

/** The class EstimatorMLBatch is implemented for Poisson distributions.
    \brief Poisson distribution ML estimator
  */
template <> class EstimatorMLBatch<PoissonDistribution> {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLBatch();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Estimate the parameters
  static void estimate(PoissonDistribution& dist,
    const std::vector<PoissonDistribution::VariableType>& points);
  /** @}
    */
};

/** The class EstimatorMLBatch is implemented for univariate linear regression.
    \brief Univariate linear regression ML estimator
  */
template <size_t M> class EstimatorMLBatch<LinearRegression<M>, M> {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLBatch();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Estimate the parameters
  static void estimate(LinearRegression<M>& dist,
    const std::vector<Eigen::Matrix<double, M, 1> >& points);
  /** @}
    */
};

#include "statistics/EstimatorMLBatch.tpp"

#endif // ESTIMATORMLBATCH
