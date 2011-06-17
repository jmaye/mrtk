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

#include "UniformDistribution.h"

#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UniformDistribution::UniformDistribution(double f64MinSupport,
  double f64MaxSupport) throw (OutOfBoundException) :
  mf64MinSupport(f64MinSupport),
  mf64MaxSupport(f64MaxSupport) {
  if (mf64MinSupport >= mf64MaxSupport)
    throw OutOfBoundException("UniformDistribution::UniformDistribution(): mf64MinSupport must be smaller than mf64MaxSupport");
}

UniformDistribution::UniformDistribution(const UniformDistribution& other) :
  mf64MinSupport(other.mf64MinSupport),
  mf64MaxSupport(other.mf64MaxSupport) {
}

UniformDistribution& UniformDistribution::operator = (const UniformDistribution&
  other) {
  mf64MinSupport = other.mf64MinSupport;
  mf64MaxSupport = other.mf64MaxSupport;
  return *this;
}

UniformDistribution::~UniformDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UniformDistribution::read(std::istream& stream) {
}

void UniformDistribution::write(std::ostream& stream) const {
}

void UniformDistribution::read(std::ifstream& stream) {
}

void UniformDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const UniformDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, UniformDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const UniformDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, UniformDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void UniformDistribution::setMinSupport(double f64Value)
  throw (OutOfBoundException) {
  mf64MinSupport = f64Value;
  if (mf64MinSupport >= mf64MaxSupport)
    throw OutOfBoundException("UniformDistribution::setMinSupport(): mf64MinSupport must be smaller than mf64MaxSupport");
}

double UniformDistribution::getMinSupport() const {
  return mf64MinSupport;
}

void UniformDistribution::setMaxSupport(double f64Value)
  throw (OutOfBoundException) {
  mf64MaxSupport = f64Value;
  if (mf64MinSupport >= mf64MaxSupport)
    throw OutOfBoundException("UniformDistribution::setMaxSupport(): mf64MinSupport must be smaller than mf64MaxSupport");
}

double UniformDistribution::getMaxSupport() const {
  return mf64MaxSupport;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double UniformDistribution::pdf(double f64X) const {
  if (f64X >= mf64MinSupport && f64X <= mf64MaxSupport)
    return 1 / (mf64MaxSupport - mf64MinSupport);
  else
    return 0;
}

double UniformDistribution::logpdf(double f64X) const
  throw (InvalidOperationException){
  throw InvalidOperationException("UniformDistribution::logpdf(): undefined");
}

double UniformDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleUniform(mf64MinSupport, mf64MaxSupport);
}
