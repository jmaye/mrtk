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

/** \file EstimatorMLBatchNormal1v.h
    \brief This file implements a batch ML estimator for univariate normal
           distributions.
  */

#ifndef ESTIMATORMLBATCHNORMAL1V_H
#define ESTIMATORMLBATCHNORMAL1V_H

#include "statistics/NormalDistribution.h"

#include <vector>

template <typename D, size_t M = 1, size_t N = 1> class EstimatorMLBatch;

/** The class EstimatorMLBatch is implemented for univariate normal
    distributions.
    \brief Univariate normal distribution batch ML estimator
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

#include "statistics/EstimatorMLBatchNormal1v.tpp"

#endif // ESTIMATORMLBATCHNORMAL1V
