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

/** \file GMMClustering.h
    \brief This file defines the GMMClustering class, which implements a GMM
           clustering algorithm
  */

#ifndef GMMCLUSTERING_H
#define GMMCLUSTERING_H

#include "exceptions/InvalidOperationException.h"

#include <vector>

#include <stdint.h>

/** This class implements a Gaussian Mixture Model algorithm based on
    Exceptation-Maximization
    \brief Gaussian Mixture Model clustering algorithm
  */
class GMMClustering {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  GMMClustering();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Clusters the input data points
  static void cluster(const std::vector<std::vector<double> >&
    inputPointsVector, uint32_t u32K, std::vector<std::vector<double> >&
    meansVector, std::vector<std::vector<std::vector<double> > >&
    variancesVector, std::vector<double>& weightsVector)
    throw (InvalidOperationException);
  /** @}
    */

protected:

};

#endif // GMMCLUSTERING_H
