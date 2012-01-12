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

template <typename X, size_t M>
LinearBasisFunction<X, M>::LinearBasisFunction(const Eigen::Matrix<X, M, 1>&
  coefficients) :
  mCoefficients(coefficients) {
}

template <typename X, size_t M>
LinearBasisFunction<X, M>::~LinearBasisFunction() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X, size_t M>
double LinearBasisFunction<X, M>::getValue(const Eigen::Matrix<X, M, 1>&
  argument) const {
  return (mCoefficients.transpose() * argument)(0);
}

template <typename X, size_t M>
const Eigen::Matrix<X, M, 1>& LinearBasisFunction<X, M>::getCoefficients()
  const {
  return mCoefficients;
}

template <typename X, size_t M>
void LinearBasisFunction<X, M>::setCoefficients(const Eigen::Matrix<X, M, 1>&
  coefficients) {
  mCoefficients = coefficients;
}
