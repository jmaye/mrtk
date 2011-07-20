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

#include <Eigen/LU>
#include <Eigen/Geometry>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
WishartDistribution<M>::WishartDistribution(double degrees, const
  Eigen::Matrix<double, M, M>& scale) {
  setDegrees(degrees);
  setScale(scale);
}

template <size_t M>
WishartDistribution<M>::WishartDistribution(const WishartDistribution<M>&
  other) :
  mDegrees(other.mDegrees),
  mScale(other.mScale),
  mInverseScale(other.mInverseScale),
  mDeterminant(other.mDeterminant),
  mNormalizer(other.mNormalizer) {
}

template <size_t M>
WishartDistribution<M>& WishartDistribution<M>::operator = (const
  WishartDistribution<M>& other) {
  mDegrees = other.mDegrees;
  mScale = other.mScale;
  mInverseScale = other.mInverseScale;
  mDeterminant = other.mDeterminant;
  mNormalizer = other.mNormalizer;
  return *this;
}

template <size_t M>
WishartDistribution<M>::~WishartDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void WishartDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void WishartDistribution<M>::write(std::ostream& stream) const {
  stream << "degrees: " << std::endl << mDegrees << std::endl
    << "scale: " << std::endl << mScale;
}

template <size_t M>
void WishartDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void WishartDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void WishartDistribution<M>::setDegrees(double degrees)
  throw (BadArgumentException<double>) {
  if (degrees <= M - 1)
    throw BadArgumentException<double>(degrees, "WishartDistribution<M>::setDegrees(): degrees must be strictly bigger than the dimension - 1");
  mDegrees = degrees;
}

template <size_t M>
double WishartDistribution<M>::getDegrees() const {
  return mDegrees;
}

template <size_t M>
void WishartDistribution<M>::setScale(const Eigen::Matrix<double, M, M>&
  scale) throw (BadArgumentException<Eigen::Matrix<double, M, M> >) {
  mTransformation = scale.llt();
  if (mTransformation.isPositiveDefinite() == false)
    throw BadArgumentException<Eigen::Matrix<double, M, M> >(scale, "WishartDistribution<M>::setScale(): scale must be positive definite");
  mDeterminant = scale.determinant();
  mInverseScale = scale.inverse();
  LogGammaFunction<double, M> logGammaFunction;
  mNormalizer = mDegrees * M * 0.5 * log(2) + mDegrees * 0.5 * log(mDeterminant)
    + logGammaFunction(0.5 * mDegrees);
  mScale = scale;
}

template <size_t M>
const Eigen::Matrix<double, M, M>& WishartDistribution<M>::getScale() const {
  return mScale;
}

template <size_t M>
const Eigen::Matrix<double, M, M>& WishartDistribution<M>::getInverseScale()
  const {
  return mInverseScale;
}

template <size_t M>
double WishartDistribution<M>::getDeterminant() const {
  return mDeterminant;
}

template <size_t M>
double WishartDistribution<M>::getNormalizer() const {
  return mNormalizer;
}

template <size_t M>
const Eigen::LLT<Eigen::Matrix<double, M, M> >&
  WishartDistribution<M>::getTransformation() const {
  return mTransformation;
}

template <size_t M>
double WishartDistribution<M>::pdf(const Eigen::Matrix<double, M, M>& value)
  const {
  return exp(logpdf(value));
}

template <size_t M>
double WishartDistribution<M>::logpdf(const Eigen::Matrix<double, M, M>& value)
  const throw (BadArgumentException<Eigen::Matrix<double, M, M> >) {
  if (value.llt().isPositiveDefinite() == false)
    throw BadArgumentException<Eigen::Matrix<double, M, M> >(value, "WishartDistribution<M>::pdf(): value must be positive definite");
  return (mDegrees - M - 1) * 0.5 * log(value.determinant())
    - 0.5 * (mInverseScale * value).trace() - mNormalizer;
}

template <size_t M>
Eigen::Matrix<double, M, M> WishartDistribution<M>::getSample() const {
  Eigen::Matrix<double, M, M> A = Eigen::Matrix<double, M, M>::Zero();
  Randomizer<double> randomizer;
  // TODO: CHECK THIS
  for (size_t i = 0; i < M; ++i)
    for (size_t j = 0; j < M; ++j) {
    if (i == j) {
      A(i, j) = randomizer.sampleGamma(0.5 * (mDegrees - i), 2.0);
      break;
    }
    else {
      A(i, j) = randomizer.sampleNormal();
    }
  }

  return mTransformation.matrixL() * A * A.transpose() * mTransformation.matrixL().transpose();
}
