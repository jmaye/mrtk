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
EstimatorML<MultinomialDistribution<M>, M>::EstimatorML() :
  mSuccessProbabilities(Eigen::Matrix<double, M, 1>::Zero()),
  mNumTrials(0),
  mNumPoints(0),
  mValid(false) {
}

template <size_t M>
EstimatorML<MultinomialDistribution<M>, M>::EstimatorML(const
  EstimatorML<MultinomialDistribution<M>, M>& other) :
  mSuccessProbabilities(other.mSuccessProbabilities),
  mNumTrials(other.mNumTrials),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M>
EstimatorML<MultinomialDistribution<M>, M>&
  EstimatorML<MultinomialDistribution<M>, M>::operator =
  (const EstimatorML<MultinomialDistribution<M>, M>& other) {
  if (this != &other) {
    mSuccessProbabilities = other.mSuccessProbabilities;
    mNumTrials = other.mNumTrials;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorML<MultinomialDistribution<M>, M>::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorML<MultinomialDistribution<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M>, M>::write(std::ostream& stream)
  const {
  stream << "success probabilities: " << mSuccessProbabilities.transpose()
    << std::endl << "number of trials:" << mNumTrials << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M>, M>::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M>, M>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorML<MultinomialDistribution<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorML<MultinomialDistribution<M>, M>::getValid() const {
  return mValid;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
EstimatorML<MultinomialDistribution<M>, M>::getSuccessProbabilities() const {
  return mSuccessProbabilities;
}

template <size_t M>
size_t EstimatorML<MultinomialDistribution<M>, M>::getNumTrials() const {
  return mNumTrials;
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M>, M>::reset() {
  mNumPoints = 0;
  mValid = false;
  mSuccessProbabilities = Eigen::Matrix<double, M, 1>::Zero();
  mNumTrials = 0;
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M>, M>::addPoint(const
  Eigen::Matrix<size_t, M, 1>& point) {
  mNumPoints++;
  if (mNumPoints == 1) {
    mNumTrials = point.sum();
    for (size_t i = 0; i < M; ++i)
      mSuccessProbabilities(i) += point(i) / (double)mNumTrials;
  }
  else {
    mNumTrials += 1.0 / mNumPoints * (point.sum() - mNumTrials);
    for (size_t i = 0; i < M; ++i)
      mSuccessProbabilities(i) += 1.0 / mNumPoints * (point(i) /
        (double)mNumTrials - mSuccessProbabilities(i));
  }
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<size_t, M, 1> >& points) {
  for (size_t i = 0; i < points.size(); ++i)
    addPoint(points[i]);
}
