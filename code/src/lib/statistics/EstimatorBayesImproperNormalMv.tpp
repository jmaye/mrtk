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

#include "utils/OuterProduct.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M> >::EstimatorBayesImproper() :
    mNumPoints(0),
    mValid(false) {
}

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M> >::EstimatorBayesImproper(const
    EstimatorBayesImproper& other) :
    mPostMeanDist(other.mPostMeanDist),
    mPostCovarianceDist(other.mPostCovarianceDist),
    mPostPredDist(other.mPostPredDist),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid),
    mValuesSum(other.mValuesSum),
    mSquaredValuesSum(other.mSquaredValuesSum) {
}

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M> >&
    EstimatorBayesImproper<NormalDistribution<M> >::operator =
    (const EstimatorBayesImproper& other) {
  if (this != &other) {
    mPostMeanDist = other.mPostMeanDist;
    mPostCovarianceDist = other.mPostCovarianceDist;
    mPostPredDist = other.mPostPredDist;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
    mValuesSum = other.mValuesSum;
    mSquaredValuesSum = other.mSquaredValuesSum;
  }
  return *this;
}

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M> >::~EstimatorBayesImproper() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::read(std::istream&
    stream) {
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::write(std::ostream&
    stream) const {
  stream << "posterior mean distribution: " << std::endl << mPostMeanDist
    << std::endl
    << "posterior mean mode: " << std::endl << mPostMeanDist.getMode()
    << std::endl
    << "posterior mean covariance: " << std::endl
    << mPostMeanDist.getCovariance() << std::endl
    << "posterior covariance distribution: " << std::endl
    << mPostCovarianceDist
    << std::endl
    << "posterior covariance mode: " << std::endl
    << mPostCovarianceDist.getMode() << std::endl
    << "posterior covariance covariance: " << std::endl
    << mPostCovarianceDist.getCovariance() << std::endl
    << "posterior predictive distribution: " << std::endl
    << mPostPredDist << std::endl
    << "posterior predictive mean: " << std::endl << mPostPredDist.getMean()
    << std::endl
    << "posterior predictive covariance: " << std::endl
    << mPostPredDist.getCovariance() << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::read(std::ifstream&
    stream) {
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::write(std::ofstream&
    stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const StudentDistribution<M>&
    EstimatorBayesImproper<NormalDistribution<M> >::getPostMeanDist() const {
  return mPostMeanDist;
}

template <size_t M>
const InvWishartDistribution<M>&
    EstimatorBayesImproper<NormalDistribution<M> >::getPostCovarianceDist()
    const {
  return mPostCovarianceDist;
}

template <size_t M>
const StudentDistribution<M>&
    EstimatorBayesImproper<NormalDistribution<M> >::getPostPredDist() const {
  return mPostPredDist;
}

template <size_t M>
size_t EstimatorBayesImproper<NormalDistribution<M> >::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorBayesImproper<NormalDistribution<M> >::getValid() const {
  return mValid;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::addPoint(const Point&
    point) {
  if (mNumPoints == 0) {
    mValuesSum = Eigen::Matrix<double, M, 1>::Zero(point.size());
    mSquaredValuesSum = Eigen::Matrix<double, M, M>::Zero(point.size(),
      point.size());
  }
  mNumPoints++;
  mValuesSum += point;
  mSquaredValuesSum += outerProduct<double, M>(point);
  try {
    mValid = true;
    const Eigen::Matrix<double, M, 1> mean = mValuesSum / mNumPoints;
    const Eigen::Matrix<double, M, M> covariance =
      mSquaredValuesSum / (mNumPoints - point.size()) -
      outerProduct<double, M>(mValuesSum) * 2 /
      ((mNumPoints - point.size()) * mNumPoints) +
      outerProduct<double, M>(mean) * ((double)mNumPoints /
      (mNumPoints - point.size()));
    mPostMeanDist.setDegrees(mNumPoints - point.size());
    mPostMeanDist.setLocation(mean);
    mPostMeanDist.setScale(covariance / mNumPoints);
    mPostCovarianceDist.setDegrees(mNumPoints - 1);
    mPostCovarianceDist.setScale(covariance * (mNumPoints - point.size()));
    mPostPredDist.setDegrees(mNumPoints - point.size());
    mPostPredDist.setLocation(mean);
    mPostPredDist.setScale(covariance * (1 + 1.0 / mNumPoints));
  }
  catch (...) {
    mValid = false;
  }
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::addPoints(const
    Container& points) {
  addPoints(points.begin(), points.end());
}
