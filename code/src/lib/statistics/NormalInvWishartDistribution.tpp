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
NormalInvWishartDistribution<M>::NormalInvWishartDistribution(const
    Eigen::Matrix<double, M, 1>& mu, double kappa, double nu, const
    Eigen::Matrix<double, M, M>& sigma) :
    mCovarianceDist(nu, sigma),
    mMargMeanDist(nu - mu.size() + 1, mu, sigma / kappa / (nu - mu.size() + 1)),
    mMu(mu),
    mKappa(kappa),
    mNu(nu),
    mSigma(sigma) {
}

template <size_t M>
NormalInvWishartDistribution<M>::NormalInvWishartDistribution(
    const NormalInvWishartDistribution& other) :
    mCovarianceDist(other.mCovarianceDist),
    mMargMeanDist(other.mMargMeanDist),
    mMu(other.mMu),
    mKappa(other.mKappa),
    mNu(other.mNu),
    mSigma(other.mSigma) {
}

template <size_t M>
NormalInvWishartDistribution<M>& NormalInvWishartDistribution<M>::
    operator = (const NormalInvWishartDistribution& other) {
  if (this != &other) {
    mCovarianceDist = other.mCovarianceDist;
    mMargMeanDist = other.mMargMeanDist;
    mMu = other.mMu;
    mKappa = other.mKappa;
    mNu = other.mNu;
    mSigma = other.mSigma;
  }
  return *this;
}

template <size_t M>
NormalInvWishartDistribution<M>::~NormalInvWishartDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void NormalInvWishartDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void NormalInvWishartDistribution<M>::write(std::ostream& stream) const {
  stream << "Covariance distribution:" << std::endl << mCovarianceDist <<
    std::endl << "Marginal mean distribution: " << std::endl << mMargMeanDist;
}

template <size_t M>
void NormalInvWishartDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void NormalInvWishartDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const InvWishartDistribution<M>& NormalInvWishartDistribution<M>::
    getCovarianceDist() const {
  return mCovarianceDist;
}

template <size_t M>
const StudentDistribution<M>& NormalInvWishartDistribution<M>::getMargMeanDist()
    const {
  return mMargMeanDist;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>& NormalInvWishartDistribution<M>::getMu()
    const {
  return mMu;
}

template <size_t M>
void NormalInvWishartDistribution<M>::setMu(const Eigen::Matrix<double, M, 1>&
    mu) {
  mMu = mu;
  mMargMeanDist.setLocation(mu);
}

template <size_t M>
double NormalInvWishartDistribution<M>::getKappa() const {
  return mKappa;
}

template <size_t M>
void NormalInvWishartDistribution<M>::setKappa(double kappa) {
  mKappa = kappa;
  mMargMeanDist.setScale(mSigma / kappa / (mNu - mMu.size() + 1));
}

template <size_t M>
double NormalInvWishartDistribution<M>::getNu() const {
  return mNu;
}

template <size_t M>
void NormalInvWishartDistribution<M>::setNu(double nu) {
  mNu = nu;
  mCovarianceDist.setDegrees(nu);
  mMargMeanDist.setDegrees(nu - mMu.size() + 1);
}

template <size_t M>
const Eigen::Matrix<double, M, M>& NormalInvWishartDistribution<M>::getSigma()
    const {
  return mSigma;
}

template <size_t M>
void NormalInvWishartDistribution<M>::setSigma(const
    Eigen::Matrix<double, M, M>& sigma) {
  mSigma = sigma;
  mCovarianceDist.setScale(sigma);
  mMargMeanDist.setScale(sigma / mKappa / (mNu - mMu.size() + 1));
}

template <size_t M>
double NormalInvWishartDistribution<M>::pdf(const RandomVariable& value) const {
  return mCovarianceDist.pdf(std::get<1>(value)) *
    NormalDistribution<M>(mMu, std::get<1>(value) / mKappa).pdf(
    std::get<0>(value));
}

template <size_t M>
typename NormalInvWishartDistribution<M>::Mode
    NormalInvWishartDistribution<M>::getMode() const {
  const Eigen::Matrix<double, M, M> covariance = mCovarianceDist.getMode();
  return Mode(NormalDistribution<M>(mMu, covariance / mKappa).getMode(),
    covariance);
}

template <size_t M>
typename NormalInvWishartDistribution<M>::RandomVariable
    NormalInvWishartDistribution<M>::getSample() const {
  const Eigen::Matrix<double, M, M> covariance = mCovarianceDist.getSample();
  return RandomVariable(
    NormalDistribution<M>(mMu, covariance / mKappa).getSample(), covariance);
}
