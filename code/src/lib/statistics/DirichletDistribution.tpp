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
#include "functions/LogBetaFunction.h"

#include <Eigen/Array>

#include <iostream>
#include <fstream>
#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
DirichletDistribution<M>::DirichletDistribution(const
  Eigen::Matrix<double, M, 1>& alphaVector) {
  setAlpha(alphaVector);
}

template <size_t M>
DirichletDistribution<M>::DirichletDistribution::DirichletDistribution(const
  DirichletDistribution<M>& other) :
  mAlphaVector(other.mAlphaVector) {
}

template <size_t M>
DirichletDistribution<M>& DirichletDistribution<M>::operator =
  (const DirichletDistribution<M>& other) {
  mAlphaVector = other.mAlphaVector;
  return *this;
}

template <size_t M>
DirichletDistribution<M>::~DirichletDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void DirichletDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void DirichletDistribution<M>::write(std::ostream& stream) const {
  stream << "mAlphaVector: " << std::endl << mAlphaVector;
}

template <size_t M>
void DirichletDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void DirichletDistribution<M>::write(std::ofstream& stream) const {
}

template <size_t M>
std::ostream& operator << (std::ostream& stream, const
  DirichletDistribution<M>& obj) {
  obj.write(stream);
  return stream;
}

template <size_t M>
std::istream& operator >> (std::istream& stream, DirichletDistribution<M>&
  obj) {
  obj.read(stream);
  return stream;
}

template <size_t M>
std::ofstream& operator << (std::ofstream& stream, const
  DirichletDistribution<M>& obj) {
  obj.write(stream);
  return stream;
}

template <size_t M>
std::ifstream& operator >> (std::ifstream& stream, DirichletDistribution<M>&
  obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void DirichletDistribution<M>::setAlpha(const Eigen::Matrix<double, M, 1>&
  alphaVector) throw (BadArgumentException<Eigen::Matrix<double, M, 1> >) {
  if ((alphaVector.cwise() <= 0).any() == true)
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(alphaVector, "DirichletDistribution<M>::setAlpha(): alphaVector must be strictly positive");
  if (M < 2)
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(alphaVector, "DirichletDistribution<M>::setAlpha(): alphaVector must contain at least 2 values");
  mAlphaVector = alphaVector;
  LogBetaFunction<double, M> logBetaFunction;
  mf64Normalizer = logBetaFunction(mAlphaVector);
}

template <size_t M>
const Eigen::Matrix<double, M, 1>& DirichletDistribution<M>::getAlpha() const {
  return mAlphaVector;
}

template <size_t M>
double DirichletDistribution<M>::getNormalizer() const {
  return mf64Normalizer;
}

template <size_t M>
double DirichletDistribution<M>::pdf(const Eigen::Matrix<double, M, 1>& value)
  const {
  return exp(logpdf(value));
}

template <size_t M>
double DirichletDistribution<M>::logpdf(const Eigen::Matrix<double, M, 1>&
  value) const throw (BadArgumentException<Eigen::Matrix<double, M, 1> >) {
  if (fabs(value.sum() - 1.0) > std::numeric_limits<double>::epsilon())
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(value, "DirichletDistribution::logpdf(): input vector must sum to 1");
  if ((value.cwise() <= 0).any() == true)
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(value, "DirichletDistribution::logpdf(): input vector must be strictly positive");
  double f64Return = 0;
  for (size_t i = 0; i < M; i++)
    f64Return += (mAlphaVector(i) - 1) * log(value(i));
  return f64Return - mf64Normalizer;
}

template <size_t M>
Eigen::Matrix<double, M, 1> DirichletDistribution<M>::getSample() const {
  static Randomizer randomizer;
  Eigen::Matrix<double, M, 1> sampleGammaVector;
  for (size_t i = 0; i < M; i++)
    sampleGammaVector(i) = randomizer.sampleGamma(mAlphaVector(i), 1);
  Eigen::Matrix<double, M, 1> sampleDirVector;
  double f64Sum = sampleGammaVector.sum();
  for (size_t i = 0; i < M; i++)
    sampleDirVector(i) = sampleGammaVector(i) / f64Sum;
  return sampleDirVector;
}
