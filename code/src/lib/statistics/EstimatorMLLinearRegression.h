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

/** \file EstimatorMLLinearRegression.h
    \brief This file implements an ML estimator for linear regression models
  */

#ifndef ESTIMATORMLLINEARREGRESSION_H
#define ESTIMATORMLLINEARREGRESSION_H

#include "statistics/LinearRegression.h"
#include "exceptions/InvalidOperationException.h"

#include <vector>

/** The class EstimatorML is implemented for multivariate linear regression.
    \brief Multivariate linear regression ML estimator
  */
template <size_t M> class EstimatorML<LinearRegression<M>, M> {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorML();
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

#include "statistics/EstimatorMLLinearRegression.tpp"

#endif // ESTIMATORMLLINEARREGRESSION
