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

#include "statistics/GammaDistribution.h"

#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GammaDistribution::GammaDistribution(double f64K, double f64Theta) {
  setK(f64K);
  setTheta(f64Theta);
}

GammaDistribution::GammaDistribution(const
  GammaDistribution& other) :
  mf64K(other.mf64K),
  mf64Theta(other.mf64Theta) {
}

GammaDistribution& GammaDistribution::operator =
  (const GammaDistribution& other) {
  mf64K = other.mf64K;
  mf64Theta = other.mf64Theta;
  return *this;
}

GammaDistribution::~GammaDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GammaDistribution::read(std::istream& stream) {
}

void GammaDistribution::write(std::ostream& stream) const {
  stream << "mf64K: " << mf64K << std::endl
    << "mf64Theta: " << mf64Theta;
}

void GammaDistribution::read(std::ifstream& stream) {
}

void GammaDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const GammaDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, GammaDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const GammaDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream,
  GammaDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void GammaDistribution::setK(double f64K)
  throw (OutOfBoundException) {
  if (f64K <= 0)
    throw OutOfBoundException("GammaDistribution::setK(): f64K must be strictly positive");
  mf64K = f64K;
  mf64Normalizer = mf64K * log(mf64Theta) + lgamma(mf64K);
}

double GammaDistribution::getK() const {
  return mf64K;
}

void GammaDistribution::setTheta(double f64Theta)
  throw (OutOfBoundException) {
  if (f64Theta <= 0)
    throw OutOfBoundException("GammaDistribution::setTheta(): f64Beta must be strictly positive");
  mf64Theta = f64Theta;
  mf64Normalizer = mf64K * log(mf64Theta) + lgamma(mf64K);
}

double GammaDistribution::getTheta() const {
  return mf64Theta;
}

double GammaDistribution::getNormalizer() const {
  return mf64Normalizer;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double GammaDistribution::pdf(double f64X) const {
  return exp(logpdf(f64X));
}

double GammaDistribution::logpdf(double f64X) const
  throw (OutOfBoundException) {
  if (f64X < 0)
    throw OutOfBoundException("GammaDistribution::logpdf(): f64X must be positive");
  return (mf64K - 1) * log(f64X) - f64X / mf64Theta - mf64Normalizer;
}

double GammaDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleGamma(mf64K, mf64Theta);
}
