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

#include <cmath>
#include <stdint.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

DirichletDistribution::DirichletDistribution(const Eigen::VectorXd&
  alphaVector) {
  setAlpha(alphaVector);
}

DirichletDistribution::DirichletDistribution(const
  DirichletDistribution& other) :
  mAlphaVector(other.mAlphaVector) {
}

DirichletDistribution& DirichletDistribution::operator =
  (const DirichletDistribution& other) {
  mAlphaVector = other.mAlphaVector;
  return *this;
}

DirichletDistribution::~DirichletDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void DirichletDistribution::read(std::istream& stream) {
}

void DirichletDistribution::write(std::ostream& stream) const {
  stream << "mAlphaVector: " << mAlphaVector;
}

void DirichletDistribution::read(std::ifstream& stream) {
}

void DirichletDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const DirichletDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, DirichletDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const DirichletDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream,
  DirichletDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void DirichletDistribution::setAlpha(const Eigen::VectorXd& alphaVector)
  throw (OutOfBoundException) {
  if ((alphaVector.cwise() <= 0).any() == true)
    throw OutOfBoundException("DirichletDistribution::setAlpha(): alphaVector must be strictly positive");
  if (alphaVector.rows() < 2)
    throw OutOfBoundException("DirichletDistribution::setAlpha(): alphaVector must contain at least 2 values");
  mAlphaVector = alphaVector;
  //TODO: change this
  LogBetaFunction<double, 256> logBetaFunction;
  mf64Normalizer = logBetaFunction(mAlphaVector);
}

const Eigen::VectorXd& DirichletDistribution::getAlpha() const {
  return mAlphaVector;
}

double DirichletDistribution::getNormalizer() const {
  return mf64Normalizer;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double DirichletDistribution::pdf(const Eigen::VectorXd& xVector) const {
  return exp(logpdf(xVector));
}

double DirichletDistribution::logpdf(const Eigen::VectorXd& xVector) const
  throw (OutOfBoundException) {
  if (fabs(xVector.sum() - 1.0) > std::numeric_limits<double>::epsilon())
    throw OutOfBoundException("DirichletDistribution::logpdf(): input vector must sum to 1");
  if ((xVector.cwise() <= 0).any() == true)
    throw OutOfBoundException("DirichletDistribution::logpdf(): input vector must be strictly positive");
  double f64Return = 0;
  for (uint32_t i = 0; i < (uint32_t)mAlphaVector.rows(); i++)
    f64Return += (mAlphaVector(i) - 1) * log(xVector(i));
  return f64Return - mf64Normalizer;
}

const Eigen::VectorXd DirichletDistribution::sample() const {
  static Randomizer randomizer;
  Eigen::VectorXd sampleGammaVector(mAlphaVector.rows());
  for (uint32_t i = 0; i < (uint32_t)mAlphaVector.rows(); i++)
    sampleGammaVector(i) = randomizer.sampleGamma(mAlphaVector(i), 1);
  Eigen::VectorXd sampleDirVector(mAlphaVector.rows());
  double f64Sum = sampleGammaVector.sum();
  for (uint32_t i = 0; i < (uint32_t)mAlphaVector.rows(); i++)
    sampleDirVector(i) = sampleGammaVector(i) / f64Sum;
  return sampleDirVector;
}
