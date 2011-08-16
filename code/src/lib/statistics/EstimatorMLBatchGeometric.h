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

/** \file EstimatorMLBatchGeometric.h
    \brief This file implements a batch ML estimator for geometric
           distributions.
  */

#ifndef ESTIMATORMLBATCHGEOMETRIC_H
#define ESTIMATORMLBATCHGEOMETRIC_H

#include "statistics/GeometricDistribution.h"

#include <vector>

/** The class EstimatorMLBatch is implemented for geometric distributions.
    \brief Geometric distribution batch ML estimator
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

#include "statistics/EstimatorMLBatchGeometric.tpp"

#endif // ESTIMATORMLBATCHGEOMETRIC
