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

#include "statistics/CategoricalDistribution.h"

#include "statistics/Randomizer.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

CategoricalDistribution::CategoricalDistribution(const Eigen::VectorXd&
  eventProbabilitiesVector) {
  setEventProbabilities(eventProbabilitiesVector);
}

CategoricalDistribution::CategoricalDistribution(const CategoricalDistribution&
  other) :
  mEventProbabilitiesVector(other.mEventProbabilitiesVector) {
}

CategoricalDistribution& CategoricalDistribution::operator = (const
  CategoricalDistribution& other) {
  mEventProbabilitiesVector = other.mEventProbabilitiesVector;
  return *this;
}

CategoricalDistribution::~CategoricalDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void CategoricalDistribution::read(std::istream& stream) {
}

void CategoricalDistribution::write(std::ostream& stream) const {
  stream << "mEventProbabilitiesVector: " << std::endl
    << mEventProbabilitiesVector;
}

void CategoricalDistribution::read(std::ifstream& stream) {
}

void CategoricalDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const CategoricalDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, CategoricalDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const CategoricalDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, CategoricalDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void CategoricalDistribution::setEventProbabilities(const Eigen::VectorXd&
  eventProbabilitiesVector) throw (OutOfBoundException) {
  if (fabs(eventProbabilitiesVector.sum() - 1.0) >
    std::numeric_limits<double>::epsilon() ||
    (eventProbabilitiesVector.cwise() < 0).any() == true)
    throw OutOfBoundException("CategoricalDistribution::setEventProbabilities(): event probabilities must sum to 1 and probabilities bigger or equal to 0");
  mEventProbabilitiesVector = eventProbabilitiesVector;
}

const Eigen::VectorXd& CategoricalDistribution::getEventProbabilities() const {
  return mEventProbabilitiesVector;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double CategoricalDistribution::pmf(uint32_t u32Event) const
  throw (OutOfBoundException) {
  if (u32Event > (uint32_t)mEventProbabilitiesVector.rows())
    throw OutOfBoundException("CategoricalDistribution::pmf(): asked event does not exist");
  return mEventProbabilitiesVector(u32Event);
}

double CategoricalDistribution::logpmf(uint32_t u32Event) const
  throw (InvalidOperationException) {
  throw InvalidOperationException("CategoricalDistribution::logpmf(): undefined operation");
}

uint32_t CategoricalDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleCategorical(mEventProbabilitiesVector);
}
