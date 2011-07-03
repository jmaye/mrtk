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
#include "functions/LogGammaFunction.h"
#include "functions/LogFactorialFunction.h"

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
template <size_t N, size_t D>
double NegativeMultinomialDistribution<M>::Traits<N, D>::pmf(const
  NegativeMultinomialDistribution<N>& distribution, const
  Eigen::Matrix<size_t, N - 1, 1>& value) {
  Eigen::Matrix<size_t, M, 1> valueMat;
  valueMat << distribution.mNumTrials, value;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t D>
double NegativeMultinomialDistribution<M>::Traits<2, D>::pmf(const
  NegativeMultinomialDistribution<2>& distribution, const size_t& value) {
  Eigen::Matrix<size_t, 2, 1> valueMat;
  valueMat << distribution.mNumTrials, value;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t N, size_t D>
double NegativeMultinomialDistribution<M>::Traits<N, D>::logpmf(const
  NegativeMultinomialDistribution<N>& distribution, const
  Eigen::Matrix<size_t, N - 1, 1>& value) {
  Eigen::Matrix<size_t, M, 1> valueMat;
  valueMat << distribution.mNumTrials, value;
  return distribution.logpmf(valueMat);
}

template <size_t M>
template <size_t D>
double NegativeMultinomialDistribution<M>::Traits<2, D>::logpmf(const
  NegativeMultinomialDistribution<2>& distribution, const size_t& value) {
  Eigen::Matrix<size_t, 2, 1> valueMat;
  valueMat << distribution.mNumTrials, value;
  return distribution.logpmf(valueMat);
}

template <size_t M>
double NegativeMultinomialDistribution<M>::pmf(const
  Eigen::Matrix<size_t, M, 1>& value) const {
  return exp(logpmf(value));
}

template <size_t M>
double NegativeMultinomialDistribution<M>::pmf(const typename
  DiscreteDistribution<size_t, M - 1>::Domain& value) const {
  return Traits<M>::pmf(*this, value);
}

template <size_t M>
double NegativeMultinomialDistribution<M>::logpmf(const
  Eigen::Matrix<size_t, M, 1>& value) const
  throw (BadArgumentException<Eigen::Matrix<size_t, M, 1> >) {
  if (value(0) != MultinomialDistribution<M>::mNumTrials)
    throw BadArgumentException<Eigen::Matrix<size_t, M, 1> >(value, "NegativeMultinomialDistribution<M>::logpmf(): value(0) must contain the trial numbers");
  LogGammaFunction<size_t> lgamma;
  double f64Sum = lgamma(value.sum()) + value(0) *
    log(MultinomialDistribution<M>::mSuccessProbabilities(0)) -
      lgamma(value(0));
  LogFactorialFunction lfactorial;
  for (size_t i = 1; i < M; i++)
    f64Sum += value(i) *
      log(MultinomialDistribution<M>::mSuccessProbabilities(i)) -
      lfactorial(value(i));
  return f64Sum;
}

template <size_t M>
double NegativeMultinomialDistribution<M>::logpmf(const typename
  DiscreteDistribution<size_t, M - 1>::Domain& value) const {
  return Traits<M>::logpmf(*this, value);
}

template <size_t M>
Eigen::Matrix<size_t, M, 1> NegativeMultinomialDistribution<M>::getSample()
  const {
  return Eigen::Matrix<size_t, M, 1>::Zero();
}
