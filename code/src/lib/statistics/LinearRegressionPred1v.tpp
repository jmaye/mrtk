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

LinearRegressionPred<2>::LinearRegressionPred(const Eigen::Matrix<double, 2, 1>&
  coefficients, const Eigen::Matrix<double, 2, 2>& coeffCovariance, double
  basis, double regressionVariance) :
  mCoefficients(coefficients),
  mCoeffCovariance(coeffCovariance),
  mRegressionVariance(regressionVariance),
  mBasis(basis) {
  Eigen::Matrix<double, 2, 1> basisTrans;
  basisTrans << 1, basis;
  setLocation((mCoefficients.transpose() * basisTrans)(0));
  setScale(mRegressionVariance * (1 + (basisTrans.transpose() *
    mCoeffCovariance * basisTrans)(0)));
}

LinearRegressionPred<2>::LinearRegressionPred(const LinearRegressionPred<2>&
  other) :
  StudentDistribution<1>(other),
  mCoefficients(other.mCoefficients),
  mCoeffCovariance(other.mCoeffCovariance),
  mRegressionVariance(other.mRegressionVariance),
  mBasis(other.mBasis) {
}

LinearRegressionPred<2>& LinearRegressionPred<2>::operator = (const
  LinearRegressionPred<2>& other) {
  if (this != &other) {
    this->StudentDistribution<1>::operator=(other);
    mCoefficients = other.mCoefficients;
    mCoeffCovariance = other.mCoeffCovariance;
    mRegressionVariance = other.mRegressionVariance;
    mBasis = other.mBasis;
  }
  return *this;
}

LinearRegressionPred<2>::~LinearRegressionPred() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void LinearRegressionPred<2>::read(std::istream& stream) {
}

void LinearRegressionPred<2>::write(std::ostream& stream) const {
  stream << "coefficients: " << std::endl << mCoefficients << std::endl
    << "coefficients covariance: " << std::endl << mCoeffCovariance << std::endl
    << "basis: " << mBasis << std::endl
    << "regression variance: " << mRegressionVariance;
}

void LinearRegressionPred<2>::read(std::ifstream& stream) {
}

void LinearRegressionPred<2>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void LinearRegressionPred<2>::setCoefficients(const Eigen::Matrix<double, 2, 1>&
  coefficients) {
  Eigen::Matrix<double, 2, 1> basisTrans;
  basisTrans << 1, mBasis;
  setLocation((coefficients.transpose() * basisTrans)(0));
  mCoefficients = coefficients;
}

const Eigen::Matrix<double, 2, 1>& LinearRegressionPred<2>::getCoefficients()
  const {
  return mCoefficients;
}

void LinearRegressionPred<2>::setCoeffCovariance(const
  Eigen::Matrix<double, 2, 2>& coeffCovariance) {
  mCoeffCovariance = coeffCovariance;
  Eigen::Matrix<double, 2, 1> basisTrans;
  basisTrans << 1, mBasis;
  setScale(mRegressionVariance * (1 + (basisTrans.transpose() *
    mCoeffCovariance * basisTrans)(0)));
}

const Eigen::Matrix<double, 2, 2>& LinearRegressionPred<2>::getCoeffCovariance()
  const {
  return mCoeffCovariance;
}

void LinearRegressionPred<2>::setRegressionVariance(double variance) {
  mRegressionVariance = variance;
  Eigen::Matrix<double, 2, 1> basisTrans;
  basisTrans << 1, mBasis;
  setScale(mRegressionVariance * (1 + (basisTrans.transpose() *
    mCoeffCovariance * basisTrans)(0)));
}

double LinearRegressionPred<2>::getRegressionVariance() const {
  return mRegressionVariance;
}

void LinearRegressionPred<2>::setBasis(double basis) {
  Eigen::Matrix<double, 2, 1> basisTrans;
  basisTrans << 1, basis;
  setLocation((mCoefficients.transpose() * basisTrans)(0));
  setScale(mRegressionVariance * (1 + (basisTrans.transpose() *
    mCoeffCovariance * basisTrans)(0)));
  mBasis = basis;
}

double LinearRegressionPred<2>::getBasis() const {
  return mBasis;
}
