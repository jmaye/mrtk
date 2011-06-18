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

NormalDistribution::NormalDistribution(double f64Mean, double f64Variance)
  throw (OutOfBoundException) :
  mf64Mean(f64Mean),
  mf64Variance(f64Variance) {
  if (mf64Variance <= 0)
    throw OutOfBoundException("NormalDistribution::NormalDistribution(): mf64Variance must be greater than 0");
}

NormalDistribution::NormalDistribution(const NormalDistribution& other) :
  mf64Mean(other.mf64Mean),
  mf64Variance(other.mf64Variance) {
}

NormalDistribution& NormalDistribution::operator = (const NormalDistribution&
  other) {
  mf64Mean = other.mf64Mean;
  mf64Variance = other.mf64Variance;
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
  if (mf64Variance <= 0)
    throw OutOfBoundException("UniGaussian::setVariance(): mf64Variance must be greater than 0");
}

double NormalDistribution::getVariance() const {
  return mf64Variance;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double NormalDistribution::pdf(double f64X) const {
  return (1.0 / sqrt(2.0 * M_PI * mf64Variance)) *
    exp(-pow(f64X - mf64Mean, 2) / (2.0 * mf64Variance));
}

double NormalDistribution::logpdf(double f64X) const {
  return -1 / 2 * (log(2.0) + log(M_PI) + log(mf64Variance)) -
    (pow(f64X - mf64Mean, 2) / (2.0 * mf64Variance));
}

double NormalDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleNormal(mf64Mean, mf64Variance);
}

double NormalDistribution::KLDivergence(const NormalDistribution& other) const {
  double f64Mu1 = mf64Mean;
  double f64Mu2 = other.mf64Mean;
  double f64Var1 = mf64Variance;
  double f64Var2 = other.mf64Variance;
  return pow(f64Mu1 - f64Mu2, 2) / (2 * f64Var2) +
    1 / 2 * (f64Var1 / f64Var2 - 1 - log(f64Var1 / f64Var2));
}

double NormalDistribution::mahalanobisDistance(double f64Value) const {
  return sqrt((f64Value - mf64Mean) / mf64Variance * (f64Value - mf64Mean));
}

double NormalDistribution::standardDeviation() const {
  return sqrt(mf64Variance);
}
