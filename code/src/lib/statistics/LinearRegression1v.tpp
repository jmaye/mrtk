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

#include "statistics/NormalDistribution.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

LinearRegression<2>::LinearRegression(const Eigen::Matrix<double, 2, 1>&
  coefficients, double variance) :
  mCoefficients(coefficients) {
  setVariance(variance);
}

LinearRegression<2>::LinearRegression(const LinearRegression<2>& other) :
  mCoefficients(other.mCoefficients),
  mVariance(other.mVariance),
  mPrecision(other.mPrecision) {
}

LinearRegression<2>& LinearRegression<2>::operator = (const LinearRegression<2>&
  other) {
  if (this != &other) {
    mCoefficients = other.mCoefficients;
    mVariance = other.mVariance;
    mPrecision = other.mPrecision;
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

void LinearRegression<2>::setVariance(double variance)
  throw (BadArgumentException<double>) {
  if (variance <= 0)
    throw BadArgumentException<double>(variance,
      "LinearRegression<2>::setVariance(): variance must be strictly positive",
      __FILE__, __LINE__);
  mVariance = variance;
  mPrecision = 1 / mVariance;
}

double LinearRegression<2>::getVariance() const {
  return mVariance;
}

double LinearRegression<2>::getPrecision() const {
  return mPrecision;
}

double LinearRegression<2>::getValue(const double& value) const {
  Eigen::Matrix<double, 2, 1> valueTrans;
  valueTrans << 1, value;
  return NormalDistribution<1>((mCoefficients.transpose() * valueTrans)(0),
    mVariance).getSample();
}
