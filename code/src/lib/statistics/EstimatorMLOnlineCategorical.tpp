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
EstimatorMLOnline<CategoricalDistribution<M>, M>::EstimatorMLOnline() :
  mNumPoints(0) {
}

template <size_t M>
EstimatorMLOnline<CategoricalDistribution<M>, M>::EstimatorMLOnline(const
  EstimatorMLOnline<CategoricalDistribution<M>, M>& other) :
  mNumPoints(other.mNumPoints) {
}

template <size_t M>
EstimatorMLOnline<CategoricalDistribution<M>, M>&
  EstimatorMLOnline<CategoricalDistribution<M>, M>::operator =
  (const EstimatorMLOnline<CategoricalDistribution<M>, M>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

template <size_t M>
EstimatorMLOnline<CategoricalDistribution<M>, M>::~EstimatorMLOnline() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::read(std::istream&
  stream) {
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::write(std::ostream&
  stream) const {
  stream << "number of points: " << mNumPoints;
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::read(std::ifstream&
  stream) {
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::write(std::ofstream&
  stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::setNumPoints(size_t
  numPoints) {
  mNumPoints = numPoints;
}

template <size_t M>
size_t EstimatorMLOnline<CategoricalDistribution<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::addPoint(
  CategoricalDistribution<M>& dist, const Eigen::Matrix<size_t, M, 1>& point) {
  mNumPoints++;
  Eigen::Matrix<double, M, 1> successProbabilities =
    Eigen::Matrix<double, M, 1>::Zero();
  if (mNumPoints == 1) {
    for (size_t i = 0; i < M; ++i)
      successProbabilities(i) += point(i);
  }
  else {
    successProbabilities = dist.getSuccessProbabilities();
    for (size_t i = 0; i < M; ++i)
      successProbabilities(i) += 1.0 / mNumPoints * (point(i) -
        successProbabilities(i));
  }
  successProbabilities /= successProbabilities.sum();
  dist.setSuccessProbabilities(successProbabilities);
}
