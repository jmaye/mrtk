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

template <typename C, size_t M>
EstimatorML<MixtureDistribution<C, M> >::EstimatorML(const
    MixtureDistribution<C, M>& initDist, size_t maxNumIter, double tol) :
    mMixtureDist(initDist),
    mLogLikelihood(0),
    mMaxNumIter(maxNumIter),
    mTol(tol),
    mNumPoints(0),
    mValid(false) {
}

template <typename C, size_t M>
EstimatorML<MixtureDistribution<C, M> >::EstimatorML(const EstimatorML& other) :
    mMixtureDist(other.mMixtureDist),
    mResponsibilities(other.mResponsibilities),
    mLogLikelihood(other.mLogLikelihood),
    mMaxNumIter(other.mMaxNumIter),
    mTol(other.mTol),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

template <typename C, size_t M>
EstimatorML<MixtureDistribution<C, M> >&
    EstimatorML<MixtureDistribution<C, M> >::operator = (const EstimatorML&
    other) {
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

template <typename C, size_t M>
EstimatorML<MixtureDistribution<C, M> >::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <typename C, size_t M>
void EstimatorML<MixtureDistribution<C, M> >::read(std::istream& stream) {
}

template <typename C, size_t M>
void EstimatorML<MixtureDistribution<C, M> >::write(std::ostream& stream)
    const {
  stream << "mixture distribution: " << std::endl << mMixtureDist << std::endl
    << "log-likelihood: " << mLogLikelihood << std::endl
    << "maxNumIter: " << mMaxNumIter << std::endl
    << "tolerance: " << mTol << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <typename C, size_t M>
void EstimatorML<MixtureDistribution<C, M> >::read(std::ifstream& stream) {
}

template <typename C, size_t M>
void EstimatorML<MixtureDistribution<C, M> >::write(std::ofstream& stream)
    const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename C, size_t M>
const MixtureDistribution<C, M>&
    EstimatorML<MixtureDistribution<C, M> >::getMixtureDist() const {
  return mMixtureDist;
}

template <typename C, size_t M>
size_t EstimatorML<MixtureDistribution<C, M> >::getNumPoints() const {
  return mNumPoints;
}

template <typename C, size_t M>
bool EstimatorML<MixtureDistribution<C, M> >::getValid() const {
  return mValid;
}

template <typename C, size_t M>
double EstimatorML<MixtureDistribution<C, M> >::getLogLikelihood() const {
  return mLogLikelihood;
}

template <typename C, size_t M>
double EstimatorML<MixtureDistribution<C, M> >::getTolerance() const {
  return mTol;
}

template <typename C, size_t M>
void EstimatorML<MixtureDistribution<C, M> >::setTolerance(double tol) {
  mTol = tol;
}

template <typename C, size_t M>
size_t EstimatorML<MixtureDistribution<C, M> >::getMaxNumIter() const {
  return mMaxNumIter;
}

template <typename C, size_t M>
void EstimatorML<MixtureDistribution<C, M> >::setMaxNumIter(size_t maxNumIter) {
  mMaxNumIter = maxNumIter;
}

template <typename C, size_t M>
void EstimatorML<MixtureDistribution<C, M> >::reset() {
  mLogLikelihood = 0;
  mNumPoints = 0;
  mValid = false;
}

template <typename C, size_t M>
size_t EstimatorML<MixtureDistribution<C, M> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
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
        mResponsibilities(row, j) =
          mMixtureDist.getAssignDistribution().getProbability(j) *
          mMixtureDist.getCompDistribution(j)(*it);
        probability += mResponsibilities(row, j);
      }
      newLogLikelihood += log(probability);
      mResponsibilities.row(row) /= mResponsibilities.row(row).sum();
    }
    if (fabs(mLogLikelihood - newLogLikelihood) < mTol)
      break;
    mLogLikelihood = newLogLikelihood;
    Eigen::Matrix<double, M, 1> numPoints(K);
    for (size_t j = 0; j < K; ++j)
      numPoints(j) = mResponsibilities.col(j).sum();
    Eigen::Matrix<double, M, 1> weights = numPoints / mNumPoints;
    mMixtureDist.setAssignDistribution(CategoricalDistribution<M>(weights));
    for (size_t j = 0; j < K; ++j) {
      EstimatorML<C> estComp;
      estComp.addPoints(itStart, itEnd, mResponsibilities.col(j), numPoints(j));
      mMixtureDist.setCompDistribution(estComp.getDistribution(), j);
    }
    numIter++;
  }
  return numIter;
}

template <typename C, size_t M>
void EstimatorML<MixtureDistribution<C, M> >::addPoints(const Container&
    points) {
  addPoints(points.begin(), points.end());
}
