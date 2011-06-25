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

#include "statistics/PoissonDistribution.h"

#include "functions/LogFactorialFunction.h"
#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PoissonDistribution::PoissonDistribution(double f64Lambda) {
  setLambda(f64Lambda);
}

PoissonDistribution::PoissonDistribution(const PoissonDistribution& other) : 
  mf64Lambda(other.mf64Lambda) {
}

PoissonDistribution& PoissonDistribution::operator = (const
  PoissonDistribution& other) {
  mf64Lambda = other.mf64Lambda;
  return *this;
}

PoissonDistribution::~PoissonDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PoissonDistribution::read(std::istream& stream) {
}

void PoissonDistribution::write(std::ostream& stream) const {
  stream << "mf64Lambda: " << mf64Lambda;
}

void PoissonDistribution::read(std::ifstream& stream) {
}

void PoissonDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const PoissonDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, PoissonDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const PoissonDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, PoissonDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void PoissonDistribution::setLambda(double f64Lambda)
  throw (OutOfBoundException) {
  if (f64Lambda <= 0)
    throw OutOfBoundException("PoissonDistribution::setLambda(): f64Lambda must be strictly positive");
  mf64Lambda = f64Lambda;
}

double PoissonDistribution::getLambda() const {
  return mf64Lambda;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double PoissonDistribution::pmf(uint32_t u32X) const {
  return exp(logpmf(u32X));
}

double PoissonDistribution::logpmf(uint32_t u32X) const {
  LogFactorialFunction logFactorialFunction;
  return u32X * log(mf64Lambda) - mf64Lambda - logFactorialFunction(u32X);
}

uint32_t PoissonDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.samplePoisson(mf64Lambda);
}
