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

#include "functions/LogFactorialFunction.h"
#include "statistics/Randomizer.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
MultinomialDistribution<M>::MultinomialDistribution(size_t numTrials, const
    Eigen::Matrix<double, M, 1>& successProbabilities) {
  setSuccessProbabilities(successProbabilities);
  setNumTrials(numTrials);
}

template <size_t M>
MultinomialDistribution<M>::MultinomialDistribution(const
    MultinomialDistribution<M>& other) :
    mSuccessProbabilities(other.mSuccessProbabilities),
    mNumTrials(other.mNumTrials) {
}

template <size_t M>
MultinomialDistribution<M>& MultinomialDistribution<M>::operator =
    (const MultinomialDistribution<M>& other) {
  if (this != &other) {
    mSuccessProbabilities = other.mSuccessProbabilities;
    mNumTrials = other.mNumTrials;
  }
  return *this;
}

template <size_t M>
MultinomialDistribution<M>::~MultinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void MultinomialDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void MultinomialDistribution<M>::write(std::ostream& stream) const {
  stream << "success probabilities: "
    << mSuccessProbabilities.transpose() << std::endl
    << "trials number: " << mNumTrials;
}

template <size_t M>
void MultinomialDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void MultinomialDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void MultinomialDistribution<M>::setSuccessProbabilities(const
    Eigen::Matrix<double, M, 1>& successProbabilities) throw
    (BadArgumentException<Eigen::Matrix<double, M, 1> >) {
  if (fabs(successProbabilities.sum() - 1.0) >
    std::numeric_limits<double>::epsilon() ||
    (successProbabilities.cwise() < 0).any())
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(
      successProbabilities,
      "MultinomialDistribution<M>::setSuccessProbabilities(): success "
      "probabilities must sum to 1 and have probabilities bigger or equal to 0",
      __FILE__, __LINE__);
  mSuccessProbabilities = successProbabilities;
}

template <size_t M>
double MultinomialDistribution<M>::getSuccessProbability(size_t idx) const
    throw (OutOfBoundException<size_t>) {
  if (idx >= (size_t)mSuccessProbabilities.size())
    throw OutOfBoundException<size_t>(idx,
      "MultinomialDistribution<M>::getSuccessProbability(): index out of bound",
      __FILE__, __LINE__);
  return mSuccessProbabilities(idx);
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
    MultinomialDistribution<M>::getSuccessProbabilities() const {
  return mSuccessProbabilities;
}

template <size_t M>
void MultinomialDistribution<M>::setNumTrials(size_t numTrials)
    throw (BadArgumentException<size_t>) {
  if (numTrials == 0)
    throw BadArgumentException<size_t>(numTrials,
      "MultinomialDistribution<M>::setNumTrials(): number of trials must be "
      "strictly positive",
      __FILE__, __LINE__);
  mNumTrials = numTrials;
}

template <size_t M>
size_t MultinomialDistribution<M>::getNumTrials() const {
  return mNumTrials;
}

template <size_t M>
template <size_t N, size_t D>
double MultinomialDistribution<M>::Traits<N, D>::pmf(const
    MultinomialDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value.sum();
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t D>
double MultinomialDistribution<M>::Traits<2, D>::pmf(const
    MultinomialDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t N, size_t D>
double MultinomialDistribution<M>::Traits<N, D>::logpmf(const
    MultinomialDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value.sum();
  return distribution.logpmf(valueMat);
}

template <size_t M>
template <size_t D>
double MultinomialDistribution<M>::Traits<2, D>::logpmf(const
    MultinomialDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value;
  return distribution.logpmf(valueMat);
}

template <size_t M>
double MultinomialDistribution<M>::pmf(const RandomVariable& value) const {
  if (value.sum() != (int)mNumTrials || (value.cwise() < 0).any())
    return 0.0;
  else
    return exp(logpmf(value));
}

template <size_t M>
double MultinomialDistribution<M>::pmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::pmf(*this, value);
}

template <size_t M>
double MultinomialDistribution<M>::logpmf(const RandomVariable& value) const
    throw (BadArgumentException<RandomVariable>) {
  if (value.sum() != (int)mNumTrials || (value.cwise() < 0).any())
    throw BadArgumentException<RandomVariable>(value,
      "MultinomialDistribution<M>::logpmf(): sum of the input vector must be "
      "equal to the number of trials and contains positive values",
      __FILE__, __LINE__);
  const LogFactorialFunction logFactorialFunction;
  double sum = logFactorialFunction(mNumTrials);
  for (size_t i = 0; i < (size_t)mSuccessProbabilities.size(); ++i)
    sum += value(i) * log(mSuccessProbabilities(i)) -
      logFactorialFunction(value(i));
  return sum;
}

template <size_t M>
double MultinomialDistribution<M>::logpmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::logpmf(*this, value);
}

template <size_t M>
typename MultinomialDistribution<M>::RandomVariable
    MultinomialDistribution<M>::getSample() const {
  const static Randomizer<double, M> randomizer;
  RandomVariable sampleVector =
    RandomVariable::Zero(mSuccessProbabilities.size());
  for (size_t i = 0; i < mNumTrials; ++i)
    sampleVector(randomizer.sampleCategorical(mSuccessProbabilities))++;
  return sampleVector;
}

template <size_t M>
typename MultinomialDistribution<M>::Mean MultinomialDistribution<M>::getMean()
    const {
  return mNumTrials * mSuccessProbabilities;
}

template <size_t M>
typename MultinomialDistribution<M>::Covariance
    MultinomialDistribution<M>::getCovariance() const {
  Covariance covariance(mSuccessProbabilities.size(),
    mSuccessProbabilities.size());
  for (size_t i = 0; i < (size_t)mSuccessProbabilities.size(); ++i) {
    covariance(i, i) = mNumTrials * mSuccessProbabilities(i) * (1 -
      mSuccessProbabilities(i));
    for (size_t j = i + 1; j < (size_t)mSuccessProbabilities.size(); ++j) {
      covariance(i, j) = -1.0 * mNumTrials * mSuccessProbabilities(i) *
        mSuccessProbabilities(j);
      covariance(j, i) = covariance(i, j);
    }
  }
  return covariance;
}
