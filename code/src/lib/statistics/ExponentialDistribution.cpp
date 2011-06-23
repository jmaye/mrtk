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

#include "statistics/ExponentialDistribution.h"

#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ExponentialDistribution::ExponentialDistribution(double f64Lambda) {
  setLambda(f64Lambda);
}

ExponentialDistribution::ExponentialDistribution(const
  ExponentialDistribution& other) :
  mf64Lambda(other.mf64Lambda){
}

ExponentialDistribution& ExponentialDistribution::operator =
  (const ExponentialDistribution& other) {
  mf64Lambda = other.mf64Lambda;
  return *this;
}

ExponentialDistribution::~ExponentialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void ExponentialDistribution::read(std::istream& stream) {
}

void ExponentialDistribution::write(std::ostream& stream) const {
  stream << "mf64Lambda: " << mf64Lambda;
}

void ExponentialDistribution::read(std::ifstream& stream) {
}

void ExponentialDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const ExponentialDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, ExponentialDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const ExponentialDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream,
  ExponentialDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void ExponentialDistribution::setLambda(double f64Lambda)
  throw (OutOfBoundException) {
  if (f64Lambda <= 0)
    throw OutOfBoundException("ExponentialDistribution::setLambda(): f64Lambda must be strictly positive");
  mf64Lambda = f64Lambda;
}

double ExponentialDistribution::getLambda() const {
  return mf64Lambda;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double ExponentialDistribution::pdf(double f64X) const {
  return exp(logpdf(f64X));
}

double ExponentialDistribution::logpdf(double f64X) const
  throw (OutOfBoundException) {
  if (f64X < 0)
    throw OutOfBoundException("ExponentialDistribution::logpdf(): f64X must be strictly positive");
  return log(mf64Lambda) -mf64Lambda * f64X;
}

double ExponentialDistribution::cdf(double f64X) const {
  return 1.0 - exp(-mf64Lambda * f64X);
}

double ExponentialDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleExponential(mf64Lambda);
}

double ExponentialDistribution::KLDivergence(const ExponentialDistribution&
  other) const {
  return log(mf64Lambda) - log(other.mf64Lambda) +
    other.mf64Lambda / mf64Lambda -1;
}
