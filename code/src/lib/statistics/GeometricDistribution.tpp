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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GeometricDistribution::GeometricDistribution(double successProbability) {
  setSuccessProbability(successProbability);
}

GeometricDistribution::GeometricDistribution(const
    GeometricDistribution& other) :
    mSuccessProbability(other.mSuccessProbability) {
}

GeometricDistribution& GeometricDistribution::operator =
    (const GeometricDistribution& other) {
  if (this != &other) {
    mSuccessProbability = other.mSuccessProbability;
  }
  return *this;
}

GeometricDistribution::~GeometricDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GeometricDistribution::read(std::istream& stream) {
}

void GeometricDistribution::write(std::ostream& stream) const {
  stream << "success probability: " << mSuccessProbability;
}

void GeometricDistribution::read(std::ifstream& stream) {
}

void GeometricDistribution::write(std::ofstream& stream) const {
}


/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void GeometricDistribution::setSuccessProbability(double successProbability)
    throw (BadArgumentException<double>) {
  if (successProbability <= 0.0 || successProbability > 1.0)
    throw BadArgumentException<double>(successProbability,
      "GeometricDistribution::setSuccessProbability(): success probability "
      "must be between 0 and 1",
      __FILE__, __LINE__);
  mSuccessProbability = successProbability;
}

double GeometricDistribution::getSuccessProbability() const {
  return mSuccessProbability;
}

double GeometricDistribution::pmf(const RandomVariable& value) const {
  if (value < 0)
    return 0.0;
  else
    return exp(logpmf(value));
}

double GeometricDistribution::logpmf(const RandomVariable& value) const
    throw (BadArgumentException<RandomVariable>) {
  if (value < 0)
    throw BadArgumentException<RandomVariable>(value,
      "GeometricDistribution::logpmf(): value must be bigger than 0",
      __FILE__, __LINE__);
  else
    return value * log(1 - mSuccessProbability) + log(mSuccessProbability);
}

double GeometricDistribution::cdf(const RandomVariable& value) const {
  if (value < 0)
    return 0.0;
  else
    return 1 - pow(1 - mSuccessProbability, value + 1);
}

GeometricDistribution::RandomVariable GeometricDistribution::getSample() const {
  const static Randomizer<double> randomizer;
  return randomizer.sampleGeometric(mSuccessProbability);
}

GeometricDistribution::Mean GeometricDistribution::getMean() const {
  return (1.0 - mSuccessProbability) / mSuccessProbability;
}

GeometricDistribution::Mode GeometricDistribution::getMode() const {
  return 0;
}

GeometricDistribution::Variance GeometricDistribution::getVariance() const {
  return (1.0 - mSuccessProbability) / (mSuccessProbability *
    mSuccessProbability);
}
