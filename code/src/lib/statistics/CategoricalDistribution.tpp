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

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/
template <size_t M>
CategoricalDistribution<M>::CategoricalDistribution(const
  Eigen::Matrix<double, M, 1>& successProbabilities) {
  setSuccessProbabilities(successProbabilities);
}

template <size_t M>
CategoricalDistribution<M>::CategoricalDistribution(const
  CategoricalDistribution<M>& other) :
  mSuccessProbabilities(other.mSuccessProbabilities) {
}

template <size_t M>
CategoricalDistribution<M>& CategoricalDistribution<M>::operator = (const
  CategoricalDistribution<M>& other) {
  mSuccessProbabilities = other.mSuccessProbabilities;
  return *this;
}

template <size_t M>
CategoricalDistribution<M>::~CategoricalDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void CategoricalDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void CategoricalDistribution<M>::write(std::ostream& stream) const {
  stream << "success probabilities: " << std::endl
    << mSuccessProbabilities;
}

template <size_t M>
void CategoricalDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void CategoricalDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void CategoricalDistribution<M>::setSuccessProbabilities(const
  Eigen::Matrix<double, M, 1>& successProbabilities) throw
  (BadArgumentException<Eigen::Matrix<double, M, 1> >) {
  if (fabs(successProbabilities.sum() - 1.0) >
    std::numeric_limits<double>::epsilon() ||
    (successProbabilities.cwise() < 0).any() == true)
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(successProbabilities,
    "CategoricalDistribution::setSuccessProbabilities(): success probabilities must sum to 1 and probabilities bigger or equal to 0");
  mSuccessProbabilities = successProbabilities;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
  CategoricalDistribution<M>::getSuccessProbabilities() const {
  return mSuccessProbabilities;
}

template <size_t M>
double CategoricalDistribution<M>::pmf(const Eigen::Matrix<size_t, M, 1>& value)
  const throw (BadArgumentException<Eigen::Matrix<size_t, M, 1> >) {
  if (value.sum() != 1)
    throw BadArgumentException<Eigen::Matrix<size_t, M, 1> >(value, "CategoricalDistribution::pmf(): value must have a 1-K encoding");
  return mSuccessProbabilities.cwise() * value;
}

template <size_t M>
Eigen::Matrix<size_t, M, 1> CategoricalDistribution<M>::getSample() const {
  static Randomizer randomizer;
  Eigen::Matrix<size_t, M, 1> sample = Eigen::Matrix<size_t, M, 1>::Zeros;
  sample[randomizer.sampleCategorical(mSuccessProbabilities)]++;
  return sample;
}
