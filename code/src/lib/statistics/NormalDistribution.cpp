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

#include "statistics/NormalDistribution.h"

#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NormalDistribution::NormalDistribution(double f64Mean, double f64Variance) :
  mf64Mean(f64Mean) {
  setVariance(f64Variance);
}

NormalDistribution::NormalDistribution(const NormalDistribution& other) :
  mf64Mean(other.mf64Mean),
  mf64Variance(other.mf64Variance),
  mf64Precision(other.mf64Precision),
  mf64StandardDeviation(other.mf64StandardDeviation),
  mf64Normalizer(other.mf64Normalizer) {
}

NormalDistribution& NormalDistribution::operator = (const NormalDistribution&
  other) {
  mf64Mean = other.mf64Mean;
  mf64Variance = other.mf64Variance;
  mf64Precision = other.mf64Precision;
  mf64StandardDeviation = other.mf64StandardDeviation;
  mf64Normalizer = other.mf64Normalizer;
  return *this;
}

NormalDistribution::~NormalDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void NormalDistribution::read(std::istream& stream) {
}

void NormalDistribution::write(std::ostream& stream) const {
  stream << "mf64Mean: " << mf64Mean << std::endl
    << "mf64Variance: " << mf64Variance;
}

void NormalDistribution::read(std::ifstream& stream) {
}

void NormalDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const NormalDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, NormalDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const NormalDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, NormalDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void NormalDistribution::setMean(double f64Mean) {
  mf64Mean = f64Mean;
}

double NormalDistribution::getMean() const {
  return mf64Mean;
}

void NormalDistribution::setVariance(double f64Variance)
  throw (OutOfBoundException) {
  mf64Variance = f64Variance;
  if (mf64Variance <= 0.0)
    throw OutOfBoundException("UniGaussian::setVariance(): mf64Variance must be greater than 0");
  mf64Precision = 1.0 / f64Variance;
  mf64StandardDeviation = sqrt(f64Variance);
  mf64Normalizer = sqrt(2.0 * M_PI * mf64Variance);
}

double NormalDistribution::getVariance() const {
  return mf64Variance;
}

double NormalDistribution::getPrecision() const {
  return mf64Precision;
}

double NormalDistribution::getStandardDeviation() const {
  return mf64StandardDeviation;
}

double NormalDistribution::getNormalizer() const {
  return mf64Normalizer;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double NormalDistribution::pdf(double f64X) const {
  return (1.0 / mf64Normalizer) *
    exp(-pow(f64X - mf64Mean, 2.0) / (2.0 * mf64Variance));
}

double NormalDistribution::logpdf(double f64X) const {
  return -0.5 * (log(2.0) + log(M_PI) + log(mf64Variance)) -
    (pow(f64X - mf64Mean, 2.0) / (2.0 * mf64Variance));
}

double NormalDistribution::cdf(double f64X) const {
  return 0.5 * (1.0 + erf((f64X - mf64Mean) / mf64Normalizer));
}

double NormalDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleNormal(mf64Mean, mf64Variance);
}

double NormalDistribution::KLDivergence(const NormalDistribution& other) const {
  return 0.5 * (log(other.mf64Variance * mf64Precision) +
    other.mf64Precision * mf64Variance - 1.0 +
    (mf64Mean - other.mf64Mean) * other.mf64Precision *
    (mf64Mean - other.mf64Mean));
}

double NormalDistribution::mahalanobisDistance(double f64Value) const {
  return sqrt((f64Value - mf64Mean) * mf64Precision * (f64Value - mf64Mean));
}
