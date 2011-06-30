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

BernoulliDistribution::BernoulliDistribution(double successProbability) {
  setSuccessProbability(successProbability);
}

BernoulliDistribution::BernoulliDistribution(const BernoulliDistribution&
  other) : 
  mSuccessProbability(other.mSuccessProbability) {
}

BernoulliDistribution& BernoulliDistribution::operator =
  (const BernoulliDistribution& other) {
  mSuccessProbability = other.mSuccessProbability;
  return *this;
}

BernoulliDistribution::~BernoulliDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BernoulliDistribution::read(std::istream& stream) {
}

void BernoulliDistribution::write(std::ostream& stream) const {
  stream << "successProbability: " << mSuccessProbability;
}

void BernoulliDistribution::read(std::ifstream& stream) {
}

void BernoulliDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BernoulliDistribution::setSuccessProbability(double successProbability)
  throw (BadArgumentException<double>) {
  if (successProbability < 0.0 || successProbability > 1.0)
    throw BadArgumentException<double>(successProbability, "BernoulliDistribution::setSuccessProbability(): success probability must be between 0 and 1");
  mSuccessProbability = successProbability;
}

double BernoulliDistribution::getSuccessProbability() const {
  return mSuccessProbability;
}

double BernoulliDistribution::pmf(const size_t& value) const
  throw (BadArgumentException<size_t>) {
  if (value > 1)
    throw BadArgumentException<size_t>(value, "BernoulliDistribution::pmf(): value must not be larger than 1");
  if (value == 1)
    return mSuccessProbability;
  else
    return 1.0 - mSuccessProbability;
}

size_t BernoulliDistribution::getSample() const {
  static Randomizer randomizer;
  return randomizer.sampleBernoulli(mSuccessProbability);
}
