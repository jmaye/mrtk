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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

EstimatorMLOnline<ExponentialDistribution>::EstimatorMLOnline() :
  mNumPoints(0) {
}

EstimatorMLOnline<ExponentialDistribution>::EstimatorMLOnline(const
  EstimatorMLOnline<ExponentialDistribution>& other) :
  mNumPoints(other.mNumPoints) {
}

EstimatorMLOnline<ExponentialDistribution>&
  EstimatorMLOnline<ExponentialDistribution>::operator =
  (const EstimatorMLOnline<ExponentialDistribution>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

EstimatorMLOnline<ExponentialDistribution>::~EstimatorMLOnline() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorMLOnline<ExponentialDistribution>::read(std::istream& stream) {
}

void EstimatorMLOnline<ExponentialDistribution>::write(std::ostream& stream)
  const {
  stream << "number of points: " << mNumPoints;
}

void EstimatorMLOnline<ExponentialDistribution>::read(std::ifstream& stream) {
}

void EstimatorMLOnline<ExponentialDistribution>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void EstimatorMLOnline<ExponentialDistribution>::setNumPoints(size_t
  numPoints) {
  mNumPoints = numPoints;
}

size_t EstimatorMLOnline<ExponentialDistribution>::getNumPoints() const {
  return mNumPoints;
}

void EstimatorMLOnline<ExponentialDistribution>::addPoint(
  ExponentialDistribution& dist, const ExponentialDistribution::VariableType&
  point) {
  mNumPoints++;
  double mean;
  if (mNumPoints == 1)
    mean = point;
  else {
    mean = dist.getMean();
    mean += 1.0 / mNumPoints * (point - mean);
  }
  dist.setRate(1.0 / mean);
}
