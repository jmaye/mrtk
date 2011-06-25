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

#include "statistics/NegativeBinomialDistribution.h"

#include "functions/LogBinomialFunction.h"
#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NegativeBinomialDistribution::NegativeBinomialDistribution(uint32_t
  u32FailuresNbr, double f64P) {
  setP(f64P);
  setFailuresNbr(u32FailuresNbr);
}

NegativeBinomialDistribution::NegativeBinomialDistribution(const
  NegativeBinomialDistribution& other) :
  mf64P(other.mf64P),
  mu32FailuresNbr(other.mu32FailuresNbr) {
}

NegativeBinomialDistribution& NegativeBinomialDistribution::operator =
  (const NegativeBinomialDistribution& other) {
  mf64P = other.mf64P;
  mu32FailuresNbr = other.mu32FailuresNbr;
  return *this;
}

NegativeBinomialDistribution::~NegativeBinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void NegativeBinomialDistribution::read(std::istream& stream) {
}

void NegativeBinomialDistribution::write(std::ostream& stream) const {
  stream << "mf64P: " << mf64P << std::endl
    << "mu32FailuresNbr: " << mu32FailuresNbr;
}

void NegativeBinomialDistribution::read(std::ifstream& stream) {
}

void NegativeBinomialDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const NegativeBinomialDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream,
  NegativeBinomialDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const NegativeBinomialDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream,
  NegativeBinomialDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void NegativeBinomialDistribution::setP(double f64P)
  throw (OutOfBoundException) {
  if (f64P < 0.0 || f64P > 1.0)
    throw OutOfBoundException("NegativeBinomialDistribution::setP(): f64P must be between 0 and 1");
  mf64P = f64P;
}

double NegativeBinomialDistribution::getP() const {
  return mf64P;
}

void NegativeBinomialDistribution::setFailuresNbr(uint32_t u32FailuresNbr)
  throw (OutOfBoundException) {
  if (u32FailuresNbr == 0)
    throw OutOfBoundException("NegativeBinomialDistribution::setFailuresNbr(): u32FailuresNbr must be larger than 0");
  mu32FailuresNbr = u32FailuresNbr;
}

uint32_t NegativeBinomialDistribution::getFailuresNbr() const {
  return mu32FailuresNbr;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double NegativeBinomialDistribution::pmf(uint32_t u32SuccNbr) const {
  return exp(logpmf(u32SuccNbr));
}

double NegativeBinomialDistribution::logpmf(uint32_t u32SuccNbr) const {
  LogBinomialFunction logBinomialFunction;
  return logBinomialFunction(u32SuccNbr + mu32FailuresNbr - 1, u32SuccNbr) +
    mu32FailuresNbr * log(1 - mf64P) + u32SuccNbr * log(mf64P);
}

uint32_t NegativeBinomialDistribution::sample() const {
  return 0.0;
}
