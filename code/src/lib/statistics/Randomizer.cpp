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

#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Randomizer::Randomizer(double f64Seed) :
  mf64Seed(f64Seed) {
  srandom((uint32_t)round(f64Seed));
}

Randomizer::Randomizer(const Randomizer& other) :
  mf64Seed(other.mf64Seed) {
}

Randomizer& Randomizer::operator = (const Randomizer& other) {
  mf64Seed = other.mf64Seed;
  return *this;
}

Randomizer::~Randomizer() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Randomizer::read(std::istream& stream) {
}

void Randomizer::write(std::ostream& stream) const {
}

void Randomizer::read(std::ifstream& stream) {
}

void Randomizer::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const Randomizer& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, Randomizer& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const Randomizer& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, Randomizer& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Randomizer::setSeed(double f64Seed) {
  mf64Seed = f64Seed;
  srandom((uint32_t)round(mf64Seed));
}

double Randomizer::getSeed() const {
  return mf64Seed;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double Randomizer::sampleUniform(double f64MinSupport, double f64MaxSupport)
  const throw (OutOfBoundException) {
  if (f64MinSupport >= f64MaxSupport)
    throw OutOfBoundException("Randomizer::sampleUniform(): f64MinSupport must be smaller than f64MaxSupport");
  double f64U = (double)random() / (double)RAND_MAX;
  return f64MinSupport + (f64MaxSupport - f64MinSupport) * f64U;
}

int32_t Randomizer::sampleUniform(int32_t i32MinSupport, int32_t i32MaxSupport)
  const throw (OutOfBoundException) {
  if (i32MinSupport > i32MaxSupport)
    throw OutOfBoundException("Randomizer::sampleUniform(): i32MinSupport must be smaller or equal to i32MaxSupport");
  double f64U = (double)random() / (double)RAND_MAX;
  return round(i32MinSupport + (i32MaxSupport - i32MinSupport) * f64U);
}

double Randomizer::sampleNormal(double f64Mean, double f64Variance) const
  throw (OutOfBoundException) {
  if (f64Variance <= 0)
    throw OutOfBoundException("Randomizer::sampleNormal(): f64Variance must be greater than 0");
  double f64U, f64V, f64S;
  do {
    f64U = 2.0 * sampleUniform(0.0, 1.0) - 1.0;
    f64V = 2.0 * sampleUniform(0.0, 1.0) - 1.0;
    f64S = f64U * f64U + f64V * f64V;
  }
  while (f64S >= 1 || f64S == 0);
  return f64U * sqrt(-2 * log(f64S) / f64S) * sqrt(f64Variance) + f64Mean;
}
