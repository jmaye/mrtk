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

template <typename D, size_t M>
EstimatorMLMixture<D, M>::EstimatorMLMixture(const MixtureDistribution<D, M>&
    initDist, size_t maxNumIter, double tol) :
    mMixtureDist(initDist),
    mLogLikelihood(0),
    mMaxNumIter(maxNumIter),
    mTol(tol),
    mNumPoints(0),
    mValid(false) {
}

template <typename D, size_t M>
EstimatorMLMixture<D, M>::EstimatorMLMixture(const EstimatorMLMixture<D, M>&
    other) :
    mMixtureDist(other.mMixtureDist),
    mResponsibilities(other.mResponsibilities),
    mLogLikelihood(other.mLogLikelihood),
    mMaxNumIter(other.mMaxNumIter),
    mTol(other.mTol),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

template <typename D, size_t M>
EstimatorMLMixture<D, M>& EstimatorMLMixture<D, M>::operator =
    (const EstimatorMLMixture<D, M>& other) {
  if (this != &other) {
    mMixtureDist = other.mMixtureDist;
    mResponsibilities = other.mResponsibilities;
    mLogLikelihood = other.mLogLikelihood;
    mMaxNumIter = other.mMaxNumIter;
    mTol = other.mTol;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <typename D, size_t M>
EstimatorMLMixture<D, M>::~EstimatorMLMixture() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <typename D, size_t M>
void EstimatorMLMixture<D, M>::read(std::istream& stream) {
}

template <typename D, size_t M>
void EstimatorMLMixture<D, M>::write(std::ostream& stream) const {
  stream << "estimated mixture distribution: " << std::endl << mMixtureDist
    << "log-likelihood: " << mLogLikelihood << std::endl
    << "maxNumIter: " << mMaxNumIter << std::endl
    << "tolerance: " << mTol << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <typename D, size_t M>
void EstimatorMLMixture<D, M>::read(std::ifstream& stream) {
}

template <typename D, size_t M>
void EstimatorMLMixture<D, M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename D, size_t M>
const MixtureDistribution<D, M>& EstimatorMLMixture<D, M>::getMixtureDist()
    const {
  return mMixtureDist;
}

template <typename D, size_t M>
size_t EstimatorMLMixture<D, M>::getNumPoints() const {
  return mNumPoints;
}

template <typename D, size_t M>
bool EstimatorMLMixture<D, M>::getValid() const {
  return mValid;
}

template <typename D, size_t M>
double EstimatorMLMixture<D, M>::getLogLikelihood() const {
  return mLogLikelihood;
}

template <typename D, size_t M>
double EstimatorMLMixture<D, M>::getTolerance() const {
  return mTol;
}

template <typename D, size_t M>
void EstimatorMLMixture<D, M>::setTolerance(double tol) {
  mTol = tol;
}

template <typename D, size_t M>
size_t EstimatorMLMixture<D, M>::getMaxNumIter() const {
  return mMaxNumIter;
}

template <typename D, size_t M>
void EstimatorMLMixture<D, M>::setMaxNumIter(size_t maxNumIter) {
  mMaxNumIter = maxNumIter;
}

template <typename D, size_t M>
void EstimatorMLMixture<D, M>::reset() {
  mNumPoints = 0;
  mLogLikelihood = 0;
  mValid = false;
}

template <typename D, size_t M>
size_t EstimatorMLMixture<D, M>::
addPoints(const ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  reset();
  size_t numIter = 0;
  const size_t K = mMixtureDist.getCompDistributions().size();
  mNumPoints = itEnd - itStart;
  if (mNumPoints == 0)
    return numIter;
  mResponsibilities.resize(mNumPoints, K);
  mLogLikelihood = -std::numeric_limits<double>::infinity();
  while (numIter != mMaxNumIter) {
    double newLogLikelihood = 0;
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      double probability = 0.0;
      const size_t row = it - itStart;
      for (size_t j = 0; j < K; ++j) {
        mResponsibilities(row, j) = mWeights(j) *
          NormalDistribution<1>(mMeans(j), mVariances(j))(*it);
        probability += mResponsibilities(row, j);
      }
      newLogLikelihood += log(probability);
      mResponsibilities.row(row) /= mResponsibilities.row(row).sum();
    }
    if (fabs(mLogLikelihood - newLogLikelihood) < mTol)
      break;
    mLogLikelihood = newLogLikelihood;
    Eigen::Matrix<double, N, 1> numPoints(K);
    for (size_t j = 0; j < K; ++j)
      numPoints(j) = mResponsibilities.col(j).sum();
    mWeights = numPoints / mNumPoints;
    mMeans = Eigen::Matrix<double, N, 1>::Zero(K);
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      for (size_t j = 0; j < K; ++j)
        mMeans(j) += mResponsibilities(row, j) * (*it);
    }
    mMeans.cwise() /= numPoints;
    mVariances = Eigen::Matrix<double, N, 1>::Zero(K);
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      for (size_t j = 0; j < K; ++j)
        mVariances(j) += mResponsibilities(row, j) * ((*it) - mMeans(j)) *
          ((*it) - mMeans(j));
    }
    mVariances.cwise() /= numPoints;
    numIter++;
  }
  mValid = true;
  return numIter;
}

template <typename D, size_t M>
void EstimatorMLMixture<D, M>::addPoints(const Container& points) {
  addPoints(points.begin(), points.end());
}
