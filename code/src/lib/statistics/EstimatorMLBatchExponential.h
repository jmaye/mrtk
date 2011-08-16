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

/** \file EstimatorMLBatchExponential.h
    \brief This file implements a batch ML estimator for exponential
           distributions.
  */

#ifndef ESTIMATORMLBATCHEXPONENTIAL_H
#define ESTIMATORMLBATCHEXPONENTIAL_H

#include "statistics/ExponentialDistribution.h"

#include <vector>

/** The class EstimatorMLBatch is implemented for exponential distributions.
    \brief Exponential distribution batch ML estimator
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

#include "statistics/EstimatorMLBatchExponential.tpp"

#endif // ESTIMATORMLBATCHEXPONENTIAL
