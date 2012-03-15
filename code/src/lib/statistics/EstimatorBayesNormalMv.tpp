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
EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    EstimatorBayes(const Eigen::Matrix<double, M, M>& covariance, const
    NormalDistribution<M>& prior) :
    mMeanDist(prior),
    mPredDist(prior.getMean(), prior.getCovariance() + covariance),
    mCovariance(covariance),
    mPrecision(covariance.inverse()) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    EstimatorBayes(const Eigen::Matrix<double, M, 1>& mean, const
    InvWishartDistribution<M>& prior) :
    mCovarianceDist(prior),
    mMean(mean) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    EstimatorBayes(const NormalInvWishartDistribution<M>& prior) :
    mMeanCovarianceDist(prior),
    mPredDist(prior.getNu() - prior.getMu().size() + 1, prior.getMu(),
      (prior.getKappa() + 1.0) / prior.getKappa() /
      (prior.getNu() - prior.getMu().size() + 1) * prior.getSigma()) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::EstimatorBayes(
    const EstimatorBayes& other) :
    mMeanDist(other.mMeanDist),
    mPredDist(other.mPredDist),
    mCovariance(other.mCovariance),
    mPrecision(other.mPrecision) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    EstimatorBayes(const EstimatorBayes& other) :
    mCovarianceDist(other.mCovarianceDist),
    mMean(other.mMean) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    EstimatorBayes(const EstimatorBayes& other) :
    mMeanCovarianceDist(other.mMeanCovarianceDist),
    mPredDist(other.mPredDist) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >&
    EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::operator =
    (const EstimatorBayes& other) {
  if (this != &other) {
    mMeanDist = other.mMeanDist;
    mPredDist = other.mPredDist;
    mCovariance = other.mCovariance;
    mPrecision = other.mPrecision;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >&
    EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mCovarianceDist = other.mCovarianceDist;
    mMean = other.mMean;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >&
    EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >
    ::operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mMeanCovarianceDist = other.mMeanCovarianceDist;
    mPredDist = other.mPredDist;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    ~EstimatorBayes() {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    ~EstimatorBayes() {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    ~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    write(std::ostream& stream) const {
  stream << "Mean distribution: " << std::endl << mMeanDist << std::endl
    << "Mean mode: " << std::endl << mMeanDist.getMode() << std::endl
    << "Mean covariance: " << std::endl << mMeanDist.getCovariance()
    << std::endl
    << "Predictive distribution: " << std::endl << mPredDist << std::endl
    << "Predictive mean: " << std::endl << mPredDist.getMean() << std::endl
    << "Predictive covariance: " << std::endl << mPredDist.getCovariance();
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    write(std::ostream& stream) const {
  stream << "Covariance distribution: " << std::endl << mCovarianceDist
    << std::endl
    << "Covariance mode: " << std::endl << mCovarianceDist.getMode()
    << std::endl
    << "Covariance covariance: " << std::endl
    << mCovarianceDist.getCovariance();
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    write(std::ostream& stream) const {
  stream << "Mean and covariance distribution: " << std::endl
    << mMeanCovarianceDist << std::endl
    << "Mean and covariance mode: " << std::endl
    << std::get<0>(mMeanCovarianceDist.getMode()) << std::endl
    << std::get<1>(mMeanCovarianceDist.getMode())
    << std::endl << "Predictive distribution: " << std::endl << mPredDist
    << std::endl
    << "Predictive mean: " << std::endl << mPredDist.getMean() << std::endl
    << "Predictive covariance: " << std::endl << mPredDist.getCovariance();
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    write(std::ofstream& stream) const {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    write(std::ofstream& stream) const {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const NormalDistribution<M>&
    EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::getDist()
    const {
  return mMeanDist;
}

template <size_t M>
const InvWishartDistribution<M>&
    EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::getDist()
    const {
  return mCovarianceDist;
}

template <size_t M>
const NormalInvWishartDistribution<M>&
    EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    getDist() const {
  return mMeanCovarianceDist;
}

template <size_t M>
const NormalDistribution<M>&
    EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    getPredDist() const {
  return mPredDist;
}

template <size_t M>
const StudentDistribution<M>&
    EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    getPredDist() const {
  return mPredDist;
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    addPoint(const Point& point) {
  const Eigen::Matrix<double, M, 1> mean =
    (mMeanDist.getPrecision() + mPrecision).inverse() *
    (mMeanDist.getPrecision() * mMeanDist.getMean() + mPrecision * point);
  const Eigen::Matrix<double, M, M> covariance =
    (mMeanDist.getPrecision() + mPrecision).inverse();
  mMeanDist.setMean(mean);
  mMeanDist.setCovariance(covariance);
  mPredDist.setMean(mean);
  mPredDist.setCovariance(mCovariance + covariance);
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    addPoint(const Point& point) {
  const double degrees = mCovarianceDist.getDegrees() + 1;
  const Eigen::Matrix<double, M, M> scale = mCovarianceDist.getScale() +
    outerProduct<double, M>(point - mMean);
  mCovarianceDist.setDegrees(degrees);
  mCovarianceDist.setScale(scale);
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    addPoint(const Point& point) {
  auto mu = mMeanCovarianceDist.getMu();
  const double kappa = mMeanCovarianceDist.getKappa();
  const double nu = mMeanCovarianceDist.getNu();
  auto sigma = mMeanCovarianceDist.getSigma();
  mMeanCovarianceDist.setMu((kappa * mu + point) / (kappa + 1));
  mMeanCovarianceDist.setKappa(kappa + 1);
  mMeanCovarianceDist.setNu(nu + 1);
  mMeanCovarianceDist.setSigma(sigma + kappa / (kappa + 1) *
    outerProduct<double, M>(point - mu));
  mPredDist.setDegrees(mMeanCovarianceDist.getNu() - mu.size() + 1);
  mPredDist.setLocation(mMeanCovarianceDist.getMu());
  mPredDist.setScale((mMeanCovarianceDist.getKappa() + 1) /
    mMeanCovarianceDist.getKappa() /
    (mMeanCovarianceDist.getNu() - mu.size() + 1) *
    mMeanCovarianceDist.getSigma());
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>,
    NormalInvWishartDistribution<M> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
