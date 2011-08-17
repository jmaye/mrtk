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

/** \file EstimatorMLMixtureNormal1v.h
    \brief This file implements a batch ML estimator for mixture of univariate
           normal distributions
  */

#ifndef ESTIMATORMLMIXTURENORMAL1V_H
#define ESTIMATORMLMIXTURENORMAL1V_H

#include "statistics/NormalDistribution.h"
#include "statistics/MixtureDistribution.h"

#include <vector>

/** The class EstimatorML is implemented for mixtures of univariate normal
    distributions.
    \brief Mixture of univariate normal distributions ML estimator
  */
template <size_t N>
class EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N> {
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
  static size_t estimate(MixtureDistribution<NormalDistribution<1>, N>& dist,
    const std::vector<double>& points, Eigen::Matrix<double, Eigen::Dynamic, N>&
    responsibilities, size_t maxNumIter = 100, double tol = 1e-6);
  /** @}
    */
};

#include "statistics/EstimatorMLMixtureNormal1v.tpp"

#endif // ESTIMATORMLMIXTURENORMAL1V
