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

#include "MultinomialDistribution.h"

#include "functions/LogFactorialFunction.h"
#include "statistics/Randomizer.h"

#include <Eigen/Array>

#include <iostream>
#include <fstream>
#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MultinomialDistribution::MultinomialDistribution(uint32_t u32TrialsNbr,
  const Eigen::VectorXd& eventProbabilitiesVector) {
  setTrialsNbr(u32TrialsNbr);
  setEventProbabilities(eventProbabilitiesVector);
}

MultinomialDistribution::MultinomialDistribution(const MultinomialDistribution&
  other) :
  mEventProbabilitiesVector(other.mEventProbabilitiesVector),
  mu32TrialsNbr(other.mu32TrialsNbr) {
}

MultinomialDistribution& MultinomialDistribution::operator =
  (const MultinomialDistribution& other) {
  mu32TrialsNbr = other.mu32TrialsNbr;
  mEventProbabilitiesVector = other.mEventProbabilitiesVector;
  return *this;
}

MultinomialDistribution::~MultinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void MultinomialDistribution::read(std::istream& stream) {
}

void MultinomialDistribution::write(std::ostream& stream) const {
  stream << "mEventProbabilitiesVector: " << std::endl
    << mEventProbabilitiesVector << std::endl
    << "mu32TrialsNbr: " << mu32TrialsNbr;
}

void MultinomialDistribution::read(std::ifstream& stream) {
}

void MultinomialDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const MultinomialDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream,
  MultinomialDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const MultinomialDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream,
  MultinomialDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void MultinomialDistribution::setEventProbabilities(const Eigen::VectorXd&
  eventProbabilitiesVector) throw (OutOfBoundException) {
  if (fabs(eventProbabilitiesVector.sum() - 1.0) >
    std::numeric_limits<double>::epsilon() ||
    (eventProbabilitiesVector.cwise() < 0).any() == true)
    throw OutOfBoundException("MultinomialDistribution::setEventProbabilities(): event probabilities must sum to 1 and having probabilities bigger or equal to 0");
  mEventProbabilitiesVector = eventProbabilitiesVector;
}

const Eigen::VectorXd& MultinomialDistribution::getEventProbabilities() const {
  return mEventProbabilitiesVector;
}

void MultinomialDistribution::setTrialsNbr(uint32_t u32TrialsNbr)
  throw (OutOfBoundException) {
  if (u32TrialsNbr == 0)
    throw OutOfBoundException("MultinomialDistribution::setTrialsNbr(): u32TrialsNbr must be larger than 0");
  mu32TrialsNbr = u32TrialsNbr;
}

uint32_t MultinomialDistribution::getTrialsNbr() const {
  return mu32TrialsNbr;
}


/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double MultinomialDistribution::pmf(const Eigen::VectorXi& xVector) const {
  return exp(logpmf(xVector));
}

double MultinomialDistribution::logpmf(const Eigen::VectorXi& xVector) const
  throw (OutOfBoundException) {
  if ((xVector.cwise() < 0).any() == true ||
    (uint32_t)xVector.sum() != mu32TrialsNbr)
    throw OutOfBoundException("MultinomialDistribution::logpmf(): sum of the input vector must be equal to the trial numbers");
  if (xVector.rows() != mEventProbabilitiesVector.rows())
    throw OutOfBoundException("MultinomialDistribution::logpmf(): input vector must have the same dimension as the event probabilities vector");
  LogFactorialFunction logFactorialFunction;
  double f64Sum = logFactorialFunction(mu32TrialsNbr);
  for (uint32_t i = 0; i < (uint32_t)xVector.rows(); i++)
    f64Sum += xVector(i) * log(mEventProbabilitiesVector(i)) -
      logFactorialFunction(xVector(i));
  return f64Sum;
}

const Eigen::VectorXi MultinomialDistribution::sample() const {
  static Randomizer randomizer;
  Eigen::VectorXi sampleVector =
    Eigen::VectorXi::Zero(mEventProbabilitiesVector.rows());
  for (uint32_t i = 0; i < mu32TrialsNbr; i++) {
    sampleVector[randomizer.sampleCategorical(mEventProbabilitiesVector)]++;
  }
  return sampleVector;
}
