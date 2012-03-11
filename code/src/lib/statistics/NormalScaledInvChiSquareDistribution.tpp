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

NormalScaledInvChiSquareDistribution::NormalScaledInvChiSquareDistribution(
    double mu, double kappa, double nu, double sigma) :
    mVarianceDist(nu, sigma),
    mMargMeanDist(nu, mu, sigma / kappa),
    mMu(mu),
    mKappa(kappa),
    mNu(nu),
    mSigma(sigma) {
}

NormalScaledInvChiSquareDistribution::NormalScaledInvChiSquareDistribution(
    const NormalScaledInvChiSquareDistribution& other) :
    mVarianceDist(other.mVarianceDist),
    mMargMeanDist(other.mMargMeanDist),
    mMu(other.mMu),
    mKappa(other.mKappa),
    mNu(other.mNu),
    mSigma(other.mSigma) {
}

NormalScaledInvChiSquareDistribution& NormalScaledInvChiSquareDistribution::
    operator = (const NormalScaledInvChiSquareDistribution& other) {
  if (this != &other) {
    mVarianceDist = other.mVarianceDist;
    mMargMeanDist = other.mMargMeanDist;
    mMu = other.mMu;
    mKappa = other.mKappa;
    mNu = other.mNu;
    mSigma = other.mSigma;
  }
  return *this;
}

NormalScaledInvChiSquareDistribution::~NormalScaledInvChiSquareDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void NormalScaledInvChiSquareDistribution::read(std::istream& stream) {
}

void NormalScaledInvChiSquareDistribution::write(std::ostream& stream) const {
  stream << "Variance distribution:" << std::endl << mVarianceDist <<
    std::endl << "Marginal mean distribution: " << std::endl << mMargMeanDist;
}

void NormalScaledInvChiSquareDistribution::read(std::ifstream& stream) {
}

void NormalScaledInvChiSquareDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const ScaledInvChiSquareDistribution& NormalScaledInvChiSquareDistribution::
    getVarianceDist() const {
  return mVarianceDist;
}

const StudentDistribution<1>& NormalScaledInvChiSquareDistribution::
    getMargMeanDist() const {
  return mMargMeanDist;
}

double NormalScaledInvChiSquareDistribution::getMu() const {
  return mMu;
}

void NormalScaledInvChiSquareDistribution::setMu(double mu) {
  mMu = mu;
  mMargMeanDist.setLocation(mu);
}

double NormalScaledInvChiSquareDistribution::getKappa() const {
  return mKappa;
}

void NormalScaledInvChiSquareDistribution::setKappa(double kappa) {
  mKappa = kappa;
  mMargMeanDist.setScale(mSigma / kappa);
}

double NormalScaledInvChiSquareDistribution::getNu() const {
  return mNu;
}

void NormalScaledInvChiSquareDistribution::setNu(double nu) {
  mNu = nu;
  mVarianceDist.setDegrees(nu);
  mMargMeanDist.setDegrees(nu);
}

double NormalScaledInvChiSquareDistribution::getSigma() const {
  return mSigma;
}

void NormalScaledInvChiSquareDistribution::setSigma(double sigma) {
  mSigma = sigma;
  mVarianceDist.setScale(sigma);
  mMargMeanDist.setScale(sigma / mKappa);
}

double NormalScaledInvChiSquareDistribution::
    pdf(const RandomVariable& value) const {
  return mVarianceDist.pdf(std::get<1>(value)) *
    NormalDistribution<1>(mMu, std::get<1>(value) / mKappa).pdf(
    std::get<0>(value));
}

NormalScaledInvChiSquareDistribution::Mode
    NormalScaledInvChiSquareDistribution::getMode() const {
  const double variance = mVarianceDist.getMode();
  return Mode(NormalDistribution<1>(mMu, variance / mKappa).getMode(),
    variance);
}

NormalScaledInvChiSquareDistribution::RandomVariable
    NormalScaledInvChiSquareDistribution::getSample() const {
  const double variance = mVarianceDist.getSample();
  return RandomVariable(
    NormalDistribution<1>(mMu, variance / mKappa).getSample(), variance);
}
