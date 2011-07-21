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

BernoulliDistribution::BernoulliDistribution(double successProbability) {
  setSuccessProbability(successProbability);
}

BernoulliDistribution::BernoulliDistribution(const BernoulliDistribution&
  other) : 
  CategoricalDistribution<2>(other) {
}

BernoulliDistribution& BernoulliDistribution::operator =
  (const BernoulliDistribution& other) {
  if (this != &other) {
    this->CategoricalDistribution<2>::operator=(other);
  }
  return *this;
}

BernoulliDistribution::~BernoulliDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BernoulliDistribution::read(std::istream& stream) {
}

void BernoulliDistribution::write(std::ostream& stream) const {
  stream << "success probability: " << mSuccessProbabilities(0);
}

void BernoulliDistribution::read(std::ifstream& stream) {
}

void BernoulliDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BernoulliDistribution::setSuccessProbability(double successProbability) {
  Eigen::Matrix<double, 2, 1> successProbabilities;
  successProbabilities(0) = successProbability;
  successProbabilities(1) = 1.0 - successProbability;
  CategoricalDistribution<2>::setSuccessProbabilities(successProbabilities);
}

double BernoulliDistribution::getSuccessProbability() const {
  return mSuccessProbabilities(0);
}
