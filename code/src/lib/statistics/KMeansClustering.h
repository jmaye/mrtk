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

/** \file KMeansClustering.h
    \brief KMeansClustering
  */

#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include "exceptions/InvalidOperationException.h"

#include <vector>

#include <stdint.h>

/** KMeansClustering
  */
class KMeansClustering {
  /** Constructors
    */
  KMeansClustering();

public:
  /** Methods
    */
  static void cluster(const std::vector<std::vector<double> >&
    inputPointsVector, std::vector<std::vector<double> >& clusterCentersVector,
    std::vector<std::vector<uint32_t> >& assignmentsVector, uint32_t u32K,
    uint32_t u32MaxIterations, double f64Tol) throw (InvalidOperationException);

protected:

};

#endif // KMEANSCLUSTERING_H
