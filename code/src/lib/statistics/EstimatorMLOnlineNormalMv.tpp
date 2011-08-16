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

template <size_t M>
EstimatorMLOnline<NormalDistribution<M>, M>::EstimatorMLOnline() :
  mNumPoints(0) {
}

template <size_t M>
EstimatorMLOnline<NormalDistribution<M>, M>::EstimatorMLOnline(const
  EstimatorMLOnline<NormalDistribution<M>, M>& other) :
  mNumPoints(other.mNumPoints) {
}

template <size_t M>
EstimatorMLOnline<NormalDistribution<M>, M>&
  EstimatorMLOnline<NormalDistribution<M>, M>::operator =
  (const EstimatorMLOnline<NormalDistribution<M>, M>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

template <size_t M>
EstimatorMLOnline<NormalDistribution<M>, M>::~EstimatorMLOnline() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::write(std::ostream& stream)
  const {
  stream << "number of points: " << mNumPoints;
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::setNumPoints(size_t
  numPoints) {
  mNumPoints = numPoints;
}

template <size_t M>
size_t EstimatorMLOnline<NormalDistribution<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::addPoint(
  NormalDistribution<M>& dist, const typename
  NormalDistribution<M>::VariableType& point) {
  mNumPoints++;
  Eigen::Matrix<double, M, 1> mean;
  if (mNumPoints == 1)
    mean = point;
  else {
    mean = dist.getMean();
    mean += 1.0 / mNumPoints * (point - mean);
  }
  Eigen::Matrix<double, M, M> covariance = dist.getCovariance();
  covariance += 1.0 / mNumPoints * ((point - mean) * (point - mean).transpose()
    - covariance);
  if (mNumPoints == 1)
    covariance = dist.getCovariance();
  dist.setMean(mean);
  try {
    dist.setCovariance(covariance);
  }
  catch (BadArgumentException<Eigen::Matrix<double, M, M> >& e) {
  }
}
