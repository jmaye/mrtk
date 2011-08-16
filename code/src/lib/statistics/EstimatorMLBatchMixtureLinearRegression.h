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

/** \file EstimatorMLBatchMixtureLinearRegression.h
    \brief This file implements a batch ML estimator for mixture of linear
           regression models
  */

#ifndef ESTIMATORMLBATCHMIXTURELINEARREGRESSION_H
#define ESTIMATORMLBATCHMIXTURELINEARREGRESSION_H

#include "statistics/LinearRegression.h"
#include "statistics/MixtureDistribution.h"
#include "exceptions/InvalidOperationException.h"

#include <vector>

/** The class EstimatorMLBatch is implemented for mixtures of linear
    regressions.
    \brief Mixture of linear regression batch ML estimator
  */
template <size_t M, size_t N>
class EstimatorMLBatch<MixtureDistribution<LinearRegression<M>, N>, M, N> {
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
  static size_t estimate(MixtureDistribution<LinearRegression<M>, N>& dist,
    const std::vector<Eigen::Matrix<double, M, 1> >& points,
    Eigen::Matrix<double, Eigen::Dynamic, N>& responsibilities, size_t
    maxNumIter = 100, double tol = 1e-6) throw (InvalidOperationException);
  /** @}
    */
};

#include "statistics/EstimatorMLBatchMixtureLinearRegression.tpp"

#endif // ESTIMATORMLBATCHMIXTURELINEARREGRESSION
