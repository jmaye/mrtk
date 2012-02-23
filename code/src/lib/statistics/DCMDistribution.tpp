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

#include <Eigen/Array>

#include "functions/LogGammaFunction.h"
#include "functions/LogFactorialFunction.h"
#include "statistics/DirichletDistribution.h"
#include "statistics/MultinomialDistribution.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
DCMDistribution<M>::DCMDistribution(size_t numTrials, const
    Eigen::Matrix<double, M, 1>& alpha) {
  setAlpha(alpha);
  setNumTrials(numTrials);
}

template <size_t M>
DCMDistribution<M>::DCMDistribution(const DCMDistribution<M>& other) :
    mAlpha(other.mAlpha),
    mNumTrials(other.mNumTrials) {
}

template <size_t M>
DCMDistribution<M>& DCMDistribution<M>::operator =
    (const DCMDistribution<M>& other) {
  if (this != &other) {
    mAlpha = other.mAlpha;
    mNumTrials = other.mNumTrials;
  }
  return *this;
}

template <size_t M>
DCMDistribution<M>::~DCMDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void DCMDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void DCMDistribution<M>::write(std::ostream& stream) const {
  stream << "alpha: " << std::endl << mAlpha.transpose() << std::endl
    << "trials number: " << mNumTrials;
}

template <size_t M>
void DCMDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void DCMDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void DCMDistribution<M>::setAlpha(const Eigen::Matrix<double, M, 1>&
    alpha) throw (BadArgumentException<Eigen::Matrix<double, M, 1> >) {
  if ((alpha.cwise() <= 0).any() == true)
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(alpha,
      "DCMDistribution<M>::setAlpha(): alpha must be strictly positive",
      __FILE__, __LINE__);
  mAlpha = alpha;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>& DCMDistribution<M>::getAlpha() const {
  return mAlpha;
}

template <size_t M>
void DCMDistribution<M>::setNumTrials(size_t numTrials)
    throw (BadArgumentException<size_t>) {
  if (numTrials == 0)
    throw BadArgumentException<size_t>(numTrials,
      "DCMDistribution<M>::setNumTrials(): number of trials must be "
      "strictly positive",
      __FILE__, __LINE__);
  mNumTrials = numTrials;
}

template <size_t M>
size_t DCMDistribution<M>::getNumTrials() const {
  return mNumTrials;
}

template <size_t M>
template <size_t N, size_t D>
double DCMDistribution<M>::Traits<N, D>::pmf(const DCMDistribution<N>&
    distribution, const Eigen::Matrix<size_t, N - 1, 1>& value) {
  if (value.sum() > distribution.mNumTrials)
    return 0.0;
  Eigen::Matrix<size_t, M, 1> valueMat;
  valueMat << distribution.mNumTrials - value.sum(), value;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t D>
double DCMDistribution<M>::Traits<2, D>::pmf(const DCMDistribution<2>&
    distribution, const size_t& value) {
  if (value > distribution.mNumTrials)
    return 0.0;
  Eigen::Matrix<size_t, 2, 1> valueMat;
  valueMat << distribution.mNumTrials - value, value;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t N, size_t D>
double DCMDistribution<M>::Traits<N, D>::logpmf(const DCMDistribution<N>&
    distribution, const Eigen::Matrix<size_t, N - 1, 1>& value) {
  if (value.sum() > distribution.mNumTrials)
    return 0.0;
  Eigen::Matrix<size_t, M, 1> valueMat;
  valueMat << distribution.mNumTrials - value.sum(), value;
  return distribution.logpmf(valueMat);
}

template <size_t M>
template <size_t D>
double DCMDistribution<M>::Traits<2, D>::logpmf(const DCMDistribution<2>&
    distribution, const size_t& value) {
  if (value > distribution.mNumTrials)
    return 0.0;
  Eigen::Matrix<size_t, 2, 1> valueMat;
  valueMat << distribution.mNumTrials - value, value;
  return distribution.logpmf(valueMat);
}

template <size_t M>
double DCMDistribution<M>::pmf(const Eigen::Matrix<size_t, M, 1>& value) const {
  if (value.sum() != mNumTrials)
    return 0.0;
  else
    return exp(logpmf(value));
}

template <size_t M>
double DCMDistribution<M>::pmf(const typename
    DiscreteDistribution<size_t, M - 1>::Domain& value) const {
  return Traits<M>::pmf(*this, value);
}

template <size_t M>
double DCMDistribution<M>::logpmf(const Eigen::Matrix<size_t, M, 1>&
    value) const throw (BadArgumentException<Eigen::Matrix<size_t, M, 1> >) {
  if (value.sum() != mNumTrials)
    throw BadArgumentException<Eigen::Matrix<size_t, M, 1> >(value,
      "DCMDistribution<M>::logpmf(): sum of the input vector must be "
      "equal to the number of trials",
      __FILE__, __LINE__);
  const LogGammaFunction<double> logGammaFunction;
  const LogFactorialFunction logFactorialFunction;
  double returnValue = logGammaFunction(mAlpha.sum()) -
    logGammaFunction(mAlpha.sum() + mNumTrials) +
    logFactorialFunction(mNumTrials);
  for (size_t i = 0; i < (size_t)mAlpha.size(); ++i)
    returnValue += logGammaFunction(value(i) + mAlpha(i)) -
      logGammaFunction(mAlpha(i)) - logFactorialFunction(value(i));
  return returnValue;
}

template <size_t M>
double DCMDistribution<M>::logpmf(const typename
    DiscreteDistribution<size_t, M - 1>::Domain& value) const {
  return Traits<M>::logpmf(*this, value);
}

template <size_t M>
Eigen::Matrix<size_t, M, 1> DCMDistribution<M>::getSample() const {
  static MultinomialDistribution<M> multDist(mNumTrials);
  static DirichletDistribution<M> dirDist;
  dirDist.setAlpha(mAlpha);
  multDist.setSuccessProbabilities(dirDist.getSample());
  return multDist.getSample();
}

template <size_t M>
Eigen::Matrix<double, M, 1> DCMDistribution<M>::getMean() const {
  return mNumTrials * mAlpha / mAlpha.sum();
}

template <size_t M>
Eigen::Matrix<double, M, M> DCMDistribution<M>::getCovariance() const {
  // TODO: CHECK THIS!
  Eigen::Matrix<double, M, M> covariance(mAlpha.size(), mAlpha.size());
  double sum = mAlpha.sum();
  for (size_t i = 0; i < (size_t)mAlpha.size(); ++i) {
    covariance(i, i) = mNumTrials * mAlpha(i) * (mNumTrials *
      (sum - mAlpha(i))) / (sum * sum * (sum + 1));
    for (size_t j = i + 1; j < (size_t)mAlpha.size(); ++j) {
      covariance(i, j) = -mAlpha(i) * mAlpha(j) / (sum * sum * (sum + 1));
      covariance(j, i) = covariance(i, j);
    }
  }
  return covariance;
}
