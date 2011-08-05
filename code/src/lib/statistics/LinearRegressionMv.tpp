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

template <size_t M>
LinearRegression<M>::LinearRegression(const Eigen::Matrix<double, M, 1>&
  coefficients, double variance) :
  mCoefficients(coefficients) {
  setVariance(variance);
}

template <size_t M>
LinearRegression<M>::LinearRegression(const LinearRegression<M>& other) :
  mCoefficients(other.mCoefficients),
  mVariance(other.mVariance),
  mPrecision(other.mPrecision) {
}

template <size_t M>
LinearRegression<M>& LinearRegression<M>::operator = (const LinearRegression<M>&
  other) {
  if (this != &other) {
    mCoefficients = other.mCoefficients;
    mVariance = other.mVariance;
    mPrecision = other.mPrecision;
  }
  return *this;
}

template <size_t M>
LinearRegression<M>::~LinearRegression() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void LinearRegression<M>::read(std::istream& stream) {
}

template <size_t M>
void LinearRegression<M>::write(std::ostream& stream) const {
  stream << "coefficients: " << std::endl << mCoefficients << std::endl
    << "variance: " << mVariance;
}

template <size_t M>
void LinearRegression<M>::read(std::ifstream& stream) {
}

template <size_t M>
void LinearRegression<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void LinearRegression<M>::setCoefficients(const Eigen::Matrix<double, M, 1>&
  coefficients) {
  mCoefficients = coefficients;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>& LinearRegression<M>::getCoefficients()
  const {
  return mCoefficients;
}

template <size_t M>
void LinearRegression<M>::setVariance(double variance)
  throw (BadArgumentException<double>) {
  if (variance <= 0)
    throw BadArgumentException<double>(variance,
      "LinearRegression<M>::setVariance(): variance must be strictly positive",
      __FILE__, __LINE__);
  mVariance = variance;
  mPrecision = 1 / mVariance;
}

template <size_t M>
double LinearRegression<M>::getVariance() const {
  return mVariance;
}

template <size_t M>
double LinearRegression<M>::getPrecision() const {
  return mPrecision;
}

template <size_t M>
double LinearRegression<M>::getValue(const Eigen::Matrix<double, M - 1, 1>&
  value) const {
  Eigen::Matrix<double, M, 1> valueTrans;
  valueTrans << 1, value;
  return NormalDistribution<1>((mCoefficients.transpose() * valueTrans)(0),
    mVariance).getSample();
}
