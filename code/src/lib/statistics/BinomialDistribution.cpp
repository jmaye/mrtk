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

#include "statistics/BinomialDistribution.h"

#include "functions/LogBinomialFunction.h"
#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BinomialDistribution::BinomialDistribution(uint32_t u32TrialsNbr, double f64P) {
  setP(f64P);
  setTrialsNbr(u32TrialsNbr);
}

BinomialDistribution::BinomialDistribution(const BinomialDistribution& other) :
  mf64P(other.mf64P),
  mu32TrialsNbr(other.mu32TrialsNbr) {
}

BinomialDistribution& BinomialDistribution::operator =
  (const BinomialDistribution& other) {
  mf64P = other.mf64P;
  mu32TrialsNbr = other.mu32TrialsNbr;
  return *this;
}

BinomialDistribution::~BinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BinomialDistribution::read(std::istream& stream) {
}

void BinomialDistribution::write(std::ostream& stream) const {
  stream << "mf64P: " << mf64P << std::endl
    << "mu32TrialsNbr: " << mu32TrialsNbr;
}

void BinomialDistribution::read(std::ifstream& stream) {
}

void BinomialDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const BinomialDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, BinomialDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const BinomialDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, BinomialDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BinomialDistribution::setP(double f64P) throw (OutOfBoundException) {
  if (f64P < 0.0 || f64P > 1.0)
    throw OutOfBoundException("BinomialDistribution::setP(): f64P must be between 0 and 1");
  mf64P = f64P;
}

double BinomialDistribution::getP() const {
  return mf64P;
}

void BinomialDistribution::setTrialsNbr(uint32_t u32TrialsNbr)
  throw (OutOfBoundException) {
  if (u32TrialsNbr == 0)
    throw OutOfBoundException("BinomialDistribution::setTrialsNbr(): u32TrialsNbr must be larger than 0");
  mu32TrialsNbr = u32TrialsNbr;
}

uint32_t BinomialDistribution::getTrialsNbr() const {
  return mu32TrialsNbr;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double BinomialDistribution::pmf(uint32_t u32SuccNbr) const {
  return exp(logpmf(u32SuccNbr));
}

double BinomialDistribution::logpmf(uint32_t u32SuccNbr) const
  throw (OutOfBoundException) {
  if (u32SuccNbr > mu32TrialsNbr)
    throw OutOfBoundException("BinomialDistribution::logpmf(): u32SuccNbr must be smaller than u32TrialsNbr");
  LogBinomialFunction logBinomialFunction;
  return logBinomialFunction(mu32TrialsNbr, u32SuccNbr) + u32SuccNbr *
    log(mf64P) + (mu32TrialsNbr - u32SuccNbr) * log(1 - mf64P);
}

uint32_t BinomialDistribution::sample() const {
  static Randomizer randomizer;
  uint32_t u32SuccNbr = 0;
  for (uint32_t i = 0; i < mu32TrialsNbr; i++)
    if (randomizer.sampleBernoulli(mf64P) == true)
      u32SuccNbr++;
  return u32SuccNbr;
}
