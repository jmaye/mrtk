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

NegativeBinomialDistribution::NegativeBinomialDistribution(size_t numTrials,
  double successProbability) :
  NegativeMultinomialDistribution<2>(numTrials) {
  setSuccessProbability(successProbability);
}

NegativeBinomialDistribution::NegativeBinomialDistribution(const
  NegativeBinomialDistribution& other) :
  NegativeMultinomialDistribution<2>(other) {
}

NegativeBinomialDistribution& NegativeBinomialDistribution::operator =
  (const NegativeBinomialDistribution& other) {
  this->NegativeMultinomialDistribution<2>::operator=(other);
  return *this;
}

NegativeBinomialDistribution::~NegativeBinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void NegativeBinomialDistribution::read(std::istream& stream) {
}

void NegativeBinomialDistribution::write(std::ostream& stream) const {
  stream << "success probability: "
    << mSuccessProbabilities(1) << std::endl
    << "trials number: " << mNumTrials;
}

void NegativeBinomialDistribution::read(std::ifstream& stream) {
}

void NegativeBinomialDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void NegativeBinomialDistribution::setSuccessProbability(double
  successProbability) {
  Eigen::Matrix<double, 2, 1> successProbabilities;
  successProbabilities(0) = 1.0 - successProbability;
  successProbabilities(1) = successProbability;
  MultinomialDistribution<2>::setSuccessProbabilities(successProbabilities);
}

double NegativeBinomialDistribution::getSuccessProbability() const {
  return mSuccessProbabilities(1);
}
