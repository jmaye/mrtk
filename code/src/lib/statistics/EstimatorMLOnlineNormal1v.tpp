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

EstimatorMLOnline<NormalDistribution<1> >::EstimatorMLOnline() :
  mNumPoints(0) {
}

EstimatorMLOnline<NormalDistribution<1> >::EstimatorMLOnline(const
  EstimatorMLOnline<NormalDistribution<1> >& other) :
  mNumPoints(other.mNumPoints) {
}

EstimatorMLOnline<NormalDistribution<1> >&
  EstimatorMLOnline<NormalDistribution<1> >::operator =
  (const EstimatorMLOnline<NormalDistribution<1> >& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

EstimatorMLOnline<NormalDistribution<1> >::~EstimatorMLOnline() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorMLOnline<NormalDistribution<1> >::read(std::istream& stream) {
}

void EstimatorMLOnline<NormalDistribution<1> >::write(std::ostream& stream)
  const {
  stream << "number of points: " << mNumPoints;
}

void EstimatorMLOnline<NormalDistribution<1> >::read(std::ifstream& stream) {
}

void EstimatorMLOnline<NormalDistribution<1> >::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void EstimatorMLOnline<NormalDistribution<1> >::setNumPoints(size_t numPoints) {
  mNumPoints = numPoints;
}

size_t EstimatorMLOnline<NormalDistribution<1> >::getNumPoints() const {
  return mNumPoints;
}

void EstimatorMLOnline<NormalDistribution<1> >::addPoint(NormalDistribution<1>&
  dist, const NormalDistribution<1>::VariableType& point) {
  mNumPoints++;
  double mean;
  if (mNumPoints == 1)
    mean = point;
  else {
    mean = dist.getMean();
    mean += 1.0 / mNumPoints * (point - mean);
  }
  double variance = dist.getVariance();
  variance += 1.0 / mNumPoints * ((point - mean) * (point - mean) - variance);
  if (variance == 0.0 || mNumPoints == 1)
    variance = dist.getVariance();
  dist.setMean(mean);
  try {
    dist.setVariance(variance);
  }
  catch (BadArgumentException<double>& e) {
  }
}
