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

#include "statistics/HyperGeometricDistribution.h"

#include "statistics/Randomizer.h"
#include "functions/LogBinomial.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

HyperGeometricDistribution::HyperGeometricDistribution(uint32_t u32N, uint32_t
  u32m, uint32_t u32n) {
  setN(u32N);
  setm(u32m);
  setn(u32n);
}

HyperGeometricDistribution::HyperGeometricDistribution(const
  HyperGeometricDistribution& other) :
  mu32N(other.mu32N),
  mu32m(other.mu32m),
  mu32n(other.mu32n) {
}

HyperGeometricDistribution& HyperGeometricDistribution::operator =
  (const HyperGeometricDistribution& other) {
  mu32N = other.mu32N;
  mu32m = other.mu32m;
  mu32n = other.mu32n;
  return *this;
}

HyperGeometricDistribution::~HyperGeometricDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void HyperGeometricDistribution::read(std::istream& stream) {
}

void HyperGeometricDistribution::write(std::ostream& stream) const {
  stream << "mu32N: " << mu32N << std::endl
    << "mu32m: " << mu32m << std::endl
    << "mu32n: " << mu32n;
}

void HyperGeometricDistribution::read(std::ifstream& stream) {
}

void HyperGeometricDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const HyperGeometricDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream,
  HyperGeometricDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const HyperGeometricDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream,
  HyperGeometricDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void HyperGeometricDistribution::setN(uint32_t u32N)
  throw (OutOfBoundException) {
  if (u32N == 0)
    throw OutOfBoundException("HyperGeometricDistribution::setN(): u32N must be strictly positive");
  mu32N = u32N;
}

uint32_t HyperGeometricDistribution::getN() const {
  return mu32N;
}

void HyperGeometricDistribution::setm(uint32_t u32m)
  throw (OutOfBoundException) {
  if (u32m > mu32N)
    throw OutOfBoundException("HyperGeometricDistribution::setm(): u32m must be smaller or equal to u32N");
  mu32m = u32m;
}

uint32_t HyperGeometricDistribution::getm() const {
  return mu32m;
}

void HyperGeometricDistribution::setn(uint32_t u32n)
  throw (OutOfBoundException) {
  if (u32n == 0 || u32n > mu32N)
    throw OutOfBoundException("HyperGeometricDistribution::setn(): u32n must be smaller or equal to u32N and strictly positive");
  mu32n = u32n;
}

uint32_t HyperGeometricDistribution::getn() const {
  return mu32n;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double HyperGeometricDistribution::pmf(uint32_t u32X) const {
  return exp(logpmf(u32X));
}

double HyperGeometricDistribution::logpmf(uint32_t u32X) const
  throw (OutOfBoundException) {
  if (u32X < std::max((uint32_t)0, mu32n + mu32m - mu32N) ||
    u32X > std::min(mu32m, mu32n))
    throw OutOfBoundException("HyperGeometricDistribution::logpmf(): u32X has invalid value");
  LogBinomial logBinomial;
  return logBinomial(mu32m, u32X) + logBinomial(mu32N - mu32m, mu32n - u32X) -
    logBinomial(mu32N, mu32n);
}

uint32_t HyperGeometricDistribution::sample() const {
  return 0.0;
}
