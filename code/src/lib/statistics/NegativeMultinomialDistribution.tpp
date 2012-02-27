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

#include <limits>

#include <Eigen/Array>

#include "functions/LogGammaFunction.h"
#include "functions/LogFactorialFunction.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
NegativeMultinomialDistribution<M>::NegativeMultinomialDistribution(size_t
    numTrials, const Eigen::Matrix<double, M, 1>& successProbabilities) {
  setSuccessProbabilities(successProbabilities);
  setNumTrials(numTrials);
}

template <size_t M>
NegativeMultinomialDistribution<M>::NegativeMultinomialDistribution(const
    NegativeMultinomialDistribution<M>& other) :
    mSuccessProbabilities(other.mSuccessProbabilities),
    mNumTrials(other.mNumTrials) {
}

template <size_t M>
NegativeMultinomialDistribution<M>&
    NegativeMultinomialDistribution<M>::operator =
    (const NegativeMultinomialDistribution<M>& other) {
  if (this != &other) {
    mSuccessProbabilities = other.mSuccessProbabilities;
    mNumTrials = other.mNumTrials;
  }
  return *this;
}

template <size_t M>
NegativeMultinomialDistribution<M>::~NegativeMultinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void NegativeMultinomialDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void NegativeMultinomialDistribution<M>::write(std::ostream& stream) const {
  stream << "success probabilities: "
    << mSuccessProbabilities.transpose() << std::endl
    << "trials number: " << mNumTrials;
}

template <size_t M>
void NegativeMultinomialDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void NegativeMultinomialDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void NegativeMultinomialDistribution<M>::setSuccessProbabilities(const
    Eigen::Matrix<double, M, 1>& successProbabilities) throw
    (BadArgumentException<Eigen::Matrix<double, M, 1> >) {
  if (fabs(successProbabilities.sum() - 1.0) >
    std::numeric_limits<double>::epsilon() ||
    (successProbabilities.cwise() < 0).any() == true)
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(
      successProbabilities,
      "NegativeMultinomialDistribution<M>::setSuccessProbabilities(): success "
      "probabilities must sum to 1 and have probabilities bigger or equal to 0",
      __FILE__, __LINE__);
  mSuccessProbabilities = successProbabilities;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
    NegativeMultinomialDistribution<M>::getSuccessProbabilities() const {
  return mSuccessProbabilities;
}

template <size_t M>
void NegativeMultinomialDistribution<M>::setNumTrials(size_t numTrials)
    throw (BadArgumentException<size_t>) {
  if (numTrials == 0)
    throw BadArgumentException<size_t>(numTrials,
      "NegativeMultinomialDistribution<M>::setNumTrials(): number of trials "
      "must be strictly positive",
      __FILE__, __LINE__);
  mNumTrials = numTrials;
}

template <size_t M>
size_t NegativeMultinomialDistribution<M>::getNumTrials() const {
  return mNumTrials;
}

template <size_t M>
template <size_t N, size_t D>
double NegativeMultinomialDistribution<M>::Traits<N, D>::pmf(const
    NegativeMultinomialDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t D>
double NegativeMultinomialDistribution<M>::Traits<2, D>::pmf(const
    NegativeMultinomialDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t N, size_t D>
double NegativeMultinomialDistribution<M>::Traits<N, D>::logpmf(const
    NegativeMultinomialDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials;
  return distribution.logpmf(valueMat);
}

template <size_t M>
template <size_t D>
double NegativeMultinomialDistribution<M>::Traits<2, D>::logpmf(const
    NegativeMultinomialDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials;
  return distribution.logpmf(valueMat);
}

template <size_t M>
double NegativeMultinomialDistribution<M>::pmf(const
    Eigen::Matrix<int, M, 1>& value) const {
  if (value(value.size() - 1) != (int)mNumTrials ||
      (value.cwise() < 0).any() == true)
    return 0.0;
  else
    return exp(logpmf(value));
}

template <size_t M>
double NegativeMultinomialDistribution<M>::pmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::pmf(*this, value);
}

template <size_t M>
double NegativeMultinomialDistribution<M>::logpmf(const
    Eigen::Matrix<int, M, 1>& value) const
    throw (BadArgumentException<Eigen::Matrix<int, M, 1> >) {
  if (value(value.size() - 1) != (int)mNumTrials ||
      (value.cwise() < 0).any() == true)
    throw BadArgumentException<Eigen::Matrix<int, M, 1> >(value,
      "NegativeMultinomialDistribution<M>::logpmf(): value(M) must contain the "
      "trial numbers and be stricly positive",
      __FILE__, __LINE__);
  const LogGammaFunction<size_t> lgamma;
  double sum = lgamma(value.sum()) - lgamma(mNumTrials) +
    mNumTrials * log(mSuccessProbabilities(value.size() - 1));
  const LogFactorialFunction lfactorial;
  for (size_t i = 0; i < (size_t)mSuccessProbabilities.size() - 1; ++i)
    sum += value(i) *
      log(mSuccessProbabilities(i)) - lfactorial(value(i));
  return sum;
}

template <size_t M>
double NegativeMultinomialDistribution<M>::logpmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::logpmf(*this, value);
}

template <size_t M>
Eigen::Matrix<int, M, 1> NegativeMultinomialDistribution<M>::getSample()
    const {
  // TODO: NOT IMPLEMENTED!
  return Eigen::Matrix<int, M, 1>::Zero(mSuccessProbabilities.size());
}

template <size_t M>
Eigen::Matrix<double, M, 1> NegativeMultinomialDistribution<M>::getMean()
    const {
  return mNumTrials / mSuccessProbabilities(mSuccessProbabilities.size() - 1) *
    mSuccessProbabilities;
}

template <size_t M>
Eigen::Matrix<double, M, M> NegativeMultinomialDistribution<M>::getCovariance()
    const {
  // TODO: COVARIANCE NOT IMPLEMENTED
  const double fail = mSuccessProbabilities(mSuccessProbabilities.size() - 1);
  return mNumTrials / fail / fail *
    mSuccessProbabilities * mSuccessProbabilities.transpose() + mNumTrials /
    fail * mSuccessProbabilities.asDiagonal();
}
