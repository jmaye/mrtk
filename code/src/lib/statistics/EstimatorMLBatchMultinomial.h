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
    \brief This file implements a batch ML estimator for multinomial
           distributions.
  */

#ifndef ESTIMATORMLBATCHMULTINOMIAL_H
#define ESTIMATORMLBATCHMULTINOMIAL_H

#include "statistics/MultinomialDistribution.h"

#include <vector>

/** The class EstimatorMLBatch is implemented for multinomial distributions.
    \brief Multinomial distribution batch ML estimator
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

#include "statistics/EstimatorMLBatchMultinomial.tpp"

#endif // ESTIMATORMLBATCHMULTINOMIAL
