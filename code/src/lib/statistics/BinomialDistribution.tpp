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

#include <gsl/gsl_sf_gamma.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BinomialDistribution::BinomialDistribution(size_t numTrials, double
    probability) :
    MultinomialDistribution<2>(numTrials) {
  setProbability(probability);
}

BinomialDistribution::BinomialDistribution(const BinomialDistribution& other) :
  MultinomialDistribution<2>(other) {
}

BinomialDistribution& BinomialDistribution::operator =
  (const BinomialDistribution& other) {
  if (this != &other) {
    MultinomialDistribution<2>::operator=(other);
  }
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
    << mProbabilities(0) << std::endl
    << "trials number: " << mNumTrials;
}

void BinomialDistribution::read(std::ifstream& stream) {
}

void BinomialDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BinomialDistribution::setProbability(double probability) {
  MultinomialDistribution<2>::setProbabilities(
    Eigen::Matrix<double, 2, 1>(probability, 1.0 - probability));
}

double BinomialDistribution::getProbability() const {
  return mProbabilities(0);
}

double BinomialDistribution::getMean() const {
  return MultinomialDistribution<2>::getMean()(0);
}

double BinomialDistribution::getMedian() const {
  return floor(mNumTrials * mProbabilities(0));
}

int BinomialDistribution::getMode() const {
  return MultinomialDistribution<2>::getMode()(0);
}

double BinomialDistribution::getVariance() const {
  return MultinomialDistribution<2>::getCovariance()(0, 0);
}

double BinomialDistribution::cmf(const int& value) const {
  if (value < 0)
    return 0;
  else if (value >= (int)mNumTrials)
    return 1;
  else
    return gsl_sf_beta_inc(mNumTrials - value, value + 1,
      1 - mProbabilities(0));
}
