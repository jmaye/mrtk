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

#include <Eigen/Array>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorBayes<MultinomialDistribution<M>, M>::EstimatorBayes(const
  Eigen::Matrix<double, M, 1>& alpha) :
  mAlpha(alpha),
  mNumPoints(0),
  mValid(false) {
}

template <size_t M>
EstimatorBayes<MultinomialDistribution<M>, M>::EstimatorBayes(const
  EstimatorBayes<MultinomialDistribution<M>, M>& other) :
  mPostSuccessDist(other.mPostSuccessDist),
  mPostPredDist(other.mPostPredDist),
  mAlpha(other.mAlpha),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M>
EstimatorBayes<MultinomialDistribution<M>, M>&
  EstimatorBayes<MultinomialDistribution<M>, M>::operator =
  (const EstimatorBayes<MultinomialDistribution<M>, M>& other) {
  if (this != &other) {
    mPostSuccessDist = other.mPostSuccessDist;
    mPostPredDist = other.mPostPredDist;
    mAlpha = other.mAlpha;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<MultinomialDistribution<M>, M>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::write(std::ostream& stream) 
const {
  stream << "posterior success probablities distribution: " << std::endl
    << mPostSuccessDist << std::endl
    << "posterior predictive distribution: " << std::endl << mPostPredDist
    << std::endl << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::read(std::ifstream&
  stream) {
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const DirichletDistribution<M>& EstimatorBayes<MultinomialDistribution<M>, M>::
getPostSuccessDist() const {
  return mPostSuccessDist;
}

template <size_t M>
const DCMDistribution<M>& EstimatorBayes<MultinomialDistribution<M>, M>::
getPostPredDist() const {
  return mPostPredDist;
}

template <size_t M>
size_t EstimatorBayes<MultinomialDistribution<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorBayes<MultinomialDistribution<M>, M>::getValid() const {
  return mValid;
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::addPoint(const
  Eigen::Matrix<size_t, M, 1>& point) {
  mNumPoints++;
  for (size_t i = 0; i < M; ++i)
    mAlpha(i) += point(i);
  mPostSuccessDist.setAlpha(mAlpha);
  mValid = true;
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<size_t, M, 1> >& points) {
  for (size_t i = 0; i < points.size(); ++i)
    addPoint(points[i]);
}
