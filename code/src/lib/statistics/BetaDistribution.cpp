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

#include "statistics/BetaDistribution.h"

#include "functions/LogBeta.h"
#include "statistics/Randomizer.h"

#include <Eigen/Core>

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BetaDistribution::BetaDistribution(double f64Alpha, double f64Beta) {
  setAlpha(f64Alpha);
  setBeta(f64Beta);
}

BetaDistribution::BetaDistribution(const
  BetaDistribution& other) :
  mf64Alpha(other.mf64Alpha),
  mf64Beta(other.mf64Beta) {
}

BetaDistribution& BetaDistribution::operator =
  (const BetaDistribution& other) {
  mf64Alpha = other.mf64Alpha;
  mf64Beta = other.mf64Beta;
  return *this;
}

BetaDistribution::~BetaDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BetaDistribution::read(std::istream& stream) {
}

void BetaDistribution::write(std::ostream& stream) const {
  stream << "mf64Alpha: " << mf64Alpha << std::endl
    << "mf64Beta: " << mf64Beta;
}

void BetaDistribution::read(std::ifstream& stream) {
}

void BetaDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const BetaDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, BetaDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const BetaDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream,
  BetaDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BetaDistribution::setAlpha(double f64Alpha)
  throw (OutOfBoundException) {
  if (f64Alpha <= 0)
    throw OutOfBoundException("BetaDistribution::setAlpha(): f64Alpha must be strictly positive");
  mf64Alpha = f64Alpha;
  LogBeta logBeta;
  mf64Normalizer = logBeta(Eigen::Vector2d(mf64Alpha, mf64Beta));
}

double BetaDistribution::getAlpha() const {
  return mf64Alpha;
}

void BetaDistribution::setBeta(double f64Beta)
  throw (OutOfBoundException) {
  if (f64Beta <= 0)
    throw OutOfBoundException("BetaDistribution::setBeta(): f64Beta must be strictly positive");
  mf64Beta = f64Beta;
  LogBeta logBeta;
  mf64Normalizer = logBeta(Eigen::Vector2d(mf64Alpha, mf64Beta));
}

double BetaDistribution::getBeta() const {
  return mf64Beta;
}

double BetaDistribution::getNormalizer() const {
  return mf64Normalizer;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double BetaDistribution::pdf(double f64X) const {
  return exp(logpdf(f64X));
}

double BetaDistribution::logpdf(double f64X) const
  throw (OutOfBoundException) {
  if (f64X < 0 || f64X > 1)
    throw OutOfBoundException("BetaDistribution::logpdf(): f64X must be in [0,1]");
  return (mf64Alpha - 1) * log(f64X) + (mf64Beta - 1) * log(1 - f64X) -
    mf64Normalizer;
}

double BetaDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleBeta(mf64Alpha, mf64Beta);
}
