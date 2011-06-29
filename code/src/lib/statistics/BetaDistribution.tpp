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

BetaDistribution::BetaDistribution(double f64Alpha, double f64Beta) :
  DirichletDistribution<2>() {
  Eigen::Matrix<double, 2, 1> alpha;
  alpha(0) = f64Alpha;
  alpha(1) = f64Beta;
  DirichletDistribution<2>::setAlpha(alpha);
}

BetaDistribution::BetaDistribution(const BetaDistribution& other) :
  DirichletDistribution<2>(other) {
}

BetaDistribution& BetaDistribution::operator = (const BetaDistribution& other) {
  this->DirichletDistribution<2>::operator=(other);
  return *this;
}

BetaDistribution::~BetaDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BetaDistribution::read(std::istream& stream) {
}

void BetaDistribution::write(std::ostream& stream) const {
  stream << "alpha: " << mAlpha(0) << std::endl << "beta: " << mAlpha(1);
}

void BetaDistribution::read(std::ifstream& stream) {
}

void BetaDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BetaDistribution::setAlpha(double f64Alpha) {
  Eigen::Matrix<double, 2, 1> alpha;
  alpha(0) = f64Alpha;
  alpha(1) = getBeta();
  DirichletDistribution<2>::setAlpha(alpha);
}

double BetaDistribution::getAlpha() const {
  return mAlpha(0);
}

void BetaDistribution::setBeta(double f64Beta) {
  Eigen::Matrix<double, 2, 1> alpha;
  alpha(0) = getAlpha();
  alpha(1) = f64Beta;
  DirichletDistribution<2>::setAlpha(alpha);
}

double BetaDistribution::getBeta() const {
  return mAlpha(1);
}
