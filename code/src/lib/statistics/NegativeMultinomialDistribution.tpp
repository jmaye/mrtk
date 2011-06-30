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

#include "statistics/Randomizer.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
NegativeMultinomialDistribution<M>::NegativeMultinomialDistribution(size_t
  numTrials, const Eigen::Matrix<double, M, 1>& successProbabilities) :
  MultinomialDistribution<M>(numTrials, successProbabilities) {
}

template <size_t M>
NegativeMultinomialDistribution<M>::NegativeMultinomialDistribution(const
  NegativeMultinomialDistribution<M>& other) :
  MultinomialDistribution<M>(other) {
}

template <size_t M>
NegativeMultinomialDistribution<M>&
  NegativeMultinomialDistribution<M>::operator =
  (const NegativeMultinomialDistribution<M>& other) {
  this->MultinomialDistribution<M>::operator=(other);
  return *this;
}

template <size_t M>
NegativeMultinomialDistribution<M>::~NegativeMultinomialDistribution() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
double NegativeMultinomialDistribution<M>::logpmf(const
  Eigen::Matrix<size_t, M, 1>& value) const
  throw (BadArgumentException<Eigen::Matrix<size_t, M, 1> >) {
  if ((value.cwise() < 0).any() == true ||
    value.sum() != MultinomialDistribution<M>::mNumTrials)
    throw BadArgumentException<Eigen::Matrix<size_t, M, 1> >(value,
      "NegativeMultinomialDistribution<M>::logpmf(): sum of the input vector must be equal to the number of trials");
  LogFactorialFunction logFactorialFunction;
  double f64Sum = logFactorialFunction(MultinomialDistribution<M>::mNumTrials);
  for (size_t i = 0; i < M; i++)
    f64Sum += value(i) *
      log(MultinomialDistribution<M>::mSuccessProbabilities(i)) -
      logFactorialFunction(value(i));
  return f64Sum;
}

template <size_t M>
Eigen::Matrix<size_t, M, 1> NegativeMultinomialDistribution<M>::getSample()
  const {
  return Eigen::Matrix<size_t, M, 1>::Zero();
}
