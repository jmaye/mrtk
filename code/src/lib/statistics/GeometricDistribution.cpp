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

#include "statistics/GeometricDistribution.h"

#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GeometricDistribution::GeometricDistribution(double f64P) {
  setP(f64P);
}

GeometricDistribution::GeometricDistribution(const
  GeometricDistribution& other) :
  mf64P(other.mf64P) {
}

GeometricDistribution& GeometricDistribution::operator =
  (const GeometricDistribution& other) {
  mf64P = other.mf64P;
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
  stream << "mf64P: " << mf64P;
}

void GeometricDistribution::read(std::ifstream& stream) {
}

void GeometricDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const GeometricDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, GeometricDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const GeometricDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, GeometricDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void GeometricDistribution::setP(double f64P) throw (OutOfBoundException) {
  if (f64P < 0.0 || f64P > 1.0)
    throw OutOfBoundException("GeometricDistribution::setP(): f64P must be between 0 and 1");
  mf64P = f64P;
}

double GeometricDistribution::getP() const {
  return mf64P;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double GeometricDistribution::pmf(uint32_t u32X) const {
  return exp(logpmf(u32X));
}

double GeometricDistribution::logpmf(uint32_t u32X) const
  throw (OutOfBoundException) {
  if (u32X == 0)
    throw OutOfBoundException("GeometricDistribution::logpdf(): u32X must be strictly positive");
  return (u32X - 1) * log(1 - mf64P) + log(mf64P);
}

uint32_t GeometricDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleGeometric(mf64P);
}
