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

#include "statistics/UniformDistributionDiscrete.h"

#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UniformDistributionDiscrete::UniformDistributionDiscrete(int32_t i32MinSupport,
  int32_t i32MaxSupport) throw (OutOfBoundException) :
  mi32MinSupport(i32MinSupport),
  mi32MaxSupport(i32MaxSupport) {
  if (mi32MinSupport > mi32MaxSupport)
    throw OutOfBoundException("UniformDistributionDiscrete::UniformDistributionDiscrete(): mi32MinSupport must be smaller or equal than mi32MaxSupport");
}

UniformDistributionDiscrete::UniformDistributionDiscrete(
  const UniformDistributionDiscrete& other) :
  mi32MinSupport(other.mi32MinSupport),
  mi32MaxSupport(other.mi32MaxSupport) {
}

UniformDistributionDiscrete& UniformDistributionDiscrete::operator =
  (const UniformDistributionDiscrete& other) {
  mi32MinSupport = other.mi32MinSupport;
  mi32MaxSupport = other.mi32MaxSupport;
  return *this;
}

UniformDistributionDiscrete::~UniformDistributionDiscrete() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UniformDistributionDiscrete::read(std::istream& stream) {
}

void UniformDistributionDiscrete::write(std::ostream& stream) const {
  stream << "mi32MinSupport: " << mi32MinSupport << std::endl
    << "mi32MaxSupport: " << mi32MaxSupport;
}

void UniformDistributionDiscrete::read(std::ifstream& stream) {
}

void UniformDistributionDiscrete::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const UniformDistributionDiscrete& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream,
  UniformDistributionDiscrete& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const UniformDistributionDiscrete& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream,
  UniformDistributionDiscrete& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void UniformDistributionDiscrete::setMinSupport(int32_t i32Value)
  throw (OutOfBoundException) {
  mi32MinSupport = i32Value;
  if (mi32MinSupport > mi32MaxSupport)
    throw OutOfBoundException("UniformDistributionDiscrete::setMinSupport(): mi32MinSupport must be smaller or equal than mi32MaxSupport");
}

int32_t UniformDistributionDiscrete::getMinSupport() const {
  return mi32MinSupport;
}

void UniformDistributionDiscrete::setMaxSupport(int32_t i32Value)
  throw (OutOfBoundException) {
  mi32MaxSupport = i32Value;
  if (mi32MinSupport > mi32MaxSupport)
    throw OutOfBoundException("UniformDistributionDiscrete::setMaxSupport(): mi32MinSupport must be smaller or equal than mi32MaxSupport");
}

int32_t UniformDistributionDiscrete::getMaxSupport() const {
  return mi32MaxSupport;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double UniformDistributionDiscrete::pmf(int32_t i32X) const {
  if (i32X >= mi32MinSupport && i32X <= mi32MaxSupport)
    return 1.0 / (mi32MaxSupport - mi32MinSupport + 1.0);
  else
    return 0.0;
}

double UniformDistributionDiscrete::logpmf(int32_t i32X) const
  throw (InvalidOperationException){
  throw InvalidOperationException("UniformDistributionDiscrete::logpmf(): undefined");
}

int32_t UniformDistributionDiscrete::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleUniform(mi32MinSupport, mi32MaxSupport);
}
