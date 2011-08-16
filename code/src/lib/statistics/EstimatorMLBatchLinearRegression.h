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

/** \file EstimatorMLBatchLinearRegression.h
    \brief This file implements a batch ML estimator for linear regression
           models
  */

#ifndef ESTIMATORMLBATCHLINEARREGRESSION_H
#define ESTIMATORMLBATCHLINEARREGRESSION_H

#include "statistics/LinearRegression.h"
#include "exceptions/InvalidOperationException.h"

#include <vector>

/** The class EstimatorMLBatch is implemented for multivariate linear
    regression.
    \brief Multivariate linear regression batch ML estimator
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
    const std::vector<Eigen::Matrix<double, M, 1> >& points, double tol = 1e-5)
    throw (InvalidOperationException);
  /** @}
    */
};

#include "statistics/EstimatorMLBatchLinearRegression.tpp"

#endif // ESTIMATORMLBATCHLINEARREGRESSION
