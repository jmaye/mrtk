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

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

EstimatorMLOnline<PoissonDistribution>::EstimatorMLOnline() :
  mNumPoints(0) {
}

EstimatorMLOnline<PoissonDistribution>::EstimatorMLOnline(const
  EstimatorMLOnline<PoissonDistribution>& other) :
  mNumPoints(other.mNumPoints) {
}

EstimatorMLOnline<PoissonDistribution>&
  EstimatorMLOnline<PoissonDistribution>::operator =
  (const EstimatorMLOnline<PoissonDistribution>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

EstimatorMLOnline<PoissonDistribution>::~EstimatorMLOnline() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorMLOnline<PoissonDistribution>::read(std::istream& stream) {
}

void EstimatorMLOnline<PoissonDistribution>::write(std::ostream& stream)
  const {
  stream << "number of points: " << mNumPoints;
}

void EstimatorMLOnline<PoissonDistribution>::read(std::ifstream& stream) {
}

void EstimatorMLOnline<PoissonDistribution>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void EstimatorMLOnline<PoissonDistribution>::setNumPoints(size_t numPoints) {
  mNumPoints = numPoints;
}

size_t EstimatorMLOnline<PoissonDistribution>::getNumPoints() const {
  return mNumPoints;
}

void EstimatorMLOnline<PoissonDistribution>::addPoint(PoissonDistribution& dist,
  const PoissonDistribution::VariableType& point) {
  mNumPoints++;
  double mean;
  if (mNumPoints == 1)
    mean = point;
  else {
    mean = dist.getMean();
    mean += 1.0 / mNumPoints * (point - mean);
  }
  if (mean == 0)
    mean = std::numeric_limits<double>::epsilon();
  dist.setRate(mean);
}
