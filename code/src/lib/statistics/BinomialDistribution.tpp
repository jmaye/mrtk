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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BinomialDistribution::BinomialDistribution(size_t numTrials, double
  successProbability) :
  MultinomialDistribution<2>(numTrials) {
  Eigen::Matrix<double, 2, 1> successProbabilities;
  successProbabilities(0) = successProbability;
  successProbabilities(1) = 1.0 - successProbability;
  MultinomialDistribution<2>::setSuccessProbabilities(successProbabilities);
}

BinomialDistribution::BinomialDistribution(const BinomialDistribution& other) :
  MultinomialDistribution<2>(other) {
}

BinomialDistribution& BinomialDistribution::operator =
  (const BinomialDistribution& other) {
  this->MultinomialDistribution<2>::operator=(other);
  return *this;
}

BinomialDistribution::~BinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BinomialDistribution::read(std::istream& stream) {
}

void BinomialDistribution::write(std::ostream& stream) const {
  stream << "success probability: "
    << mSuccessProbabilities(0) << std::endl
    << "trials number: " << mNumTrials;
}

void BinomialDistribution::read(std::ifstream& stream) {
}

void BinomialDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BinomialDistribution::setSuccessProbability(double successProbability) {
  Eigen::Matrix<double, 2, 1> successProbabilities;
  successProbabilities(0) = successProbability;
  successProbabilities(1) = 1.0 - successProbability;
  MultinomialDistribution<2>::setSuccessProbabilities(successProbabilities);
}

double BinomialDistribution::getSuccessProbability() const {
  return mSuccessProbabilities(0);
}
