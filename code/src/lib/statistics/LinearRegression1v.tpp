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

LinearRegression<2>::LinearRegression(const Eigen::Matrix<double, 2, 1>&
  coefficients, double basis, double variance) :
  mCoefficients(coefficients),
  mBasis(basis) {
  Eigen::Matrix<double, 2, 1> basisTrans;
  basisTrans << 1, basis;
  setMean((mCoefficients.transpose() * basisTrans)(0));
  setVariance(variance);
}

LinearRegression<2>::LinearRegression(const LinearRegression<2>& other) :
  NormalDistribution<1>(other),
  mCoefficients(other.mCoefficients),
  mBasis(other.mBasis) {
}

LinearRegression<2>& LinearRegression<2>::operator = (const LinearRegression<2>&
  other) {
  if (this != &other) {
    this->NormalDistribution<1>::operator=(other);
    mCoefficients = other.mCoefficients;
    mBasis = other.mBasis;
  }
  return *this;
}

LinearRegression<2>::~LinearRegression() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void LinearRegression<2>::read(std::istream& stream) {
}

void LinearRegression<2>::write(std::ostream& stream) const {
  stream << "coefficients: " << std::endl << mCoefficients << std::endl
    << "basis: " << mBasis << std::endl
    << "variance: " << mVariance;
}

void LinearRegression<2>::read(std::ifstream& stream) {
}

void LinearRegression<2>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void LinearRegression<2>::setCoefficients(const Eigen::Matrix<double, 2, 1>&
  coefficients) {
  mCoefficients = coefficients;
}

const Eigen::Matrix<double, 2, 1>& LinearRegression<2>::getCoefficients()
  const {
  return mCoefficients;
}

void LinearRegression<2>::setBasis(double basis) {
  Eigen::Matrix<double, 2, 1> basisTrans;
  basisTrans << 1, basis;
  setMean((mCoefficients.transpose() * basisTrans)(0));
  mBasis = basis;
}

double LinearRegression<2>::getBasis() const {
  return mBasis;
}
