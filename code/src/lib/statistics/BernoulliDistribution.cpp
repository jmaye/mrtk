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

#include "statistics/BernoulliDistribution.h"

#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BernoulliDistribution::BernoulliDistribution(double f64P) {
  setP(f64P);
}

BernoulliDistribution::BernoulliDistribution(const BernoulliDistribution&
  other) : 
  mf64P(other.mf64P) {
}

BernoulliDistribution& BernoulliDistribution::operator =
  (const BernoulliDistribution& other) {
  mf64P = other.mf64P;
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
  stream << "mf64P: " << mf64P;
}

void BernoulliDistribution::read(std::ifstream& stream) {
}

void BernoulliDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const BernoulliDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, BernoulliDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const BernoulliDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, BernoulliDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BernoulliDistribution::setP(double f64P) throw (OutOfBoundException) {
  if (f64P < 0.0 || f64P > 1.0)
    throw OutOfBoundException("BernoulliDistribution::setP(): f64P must be between 0 and 1");
  mf64P = f64P;
}

double BernoulliDistribution::getP() const {
  return mf64P;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double BernoulliDistribution::pmf(bool bX) const {
  if (bX == true)
    return mf64P;
  else
    return 1 - mf64P;
}

double BernoulliDistribution::logpmf(bool bX) const
  throw (InvalidOperationException) {
  throw InvalidOperationException("BernoulliDistribution::logpmf(): Undefined operation");
}

bool BernoulliDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleBernoulli(mf64P);
}
