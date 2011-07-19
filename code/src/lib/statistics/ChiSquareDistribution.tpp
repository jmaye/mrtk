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

#include "statistics/Randomizer.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ChiSquareDistribution::ChiSquareDistribution(size_t degrees) :
  GammaDistribution<>(0.5 * degrees, 2.0) {
}

ChiSquareDistribution::ChiSquareDistribution(const ChiSquareDistribution&
  other) :
  GammaDistribution<>(other) {
}

ChiSquareDistribution& ChiSquareDistribution::operator =
  (const ChiSquareDistribution& other) {
  this->GammaDistribution<>::operator=(other);
  return *this;
}

ChiSquareDistribution::~ChiSquareDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void ChiSquareDistribution::read(std::istream& stream) {
}

void ChiSquareDistribution::write(std::ostream& stream) const {
  stream << "degrees: " << getShape() * 2;
}

void ChiSquareDistribution::read(std::ifstream& stream) {
}

void ChiSquareDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void ChiSquareDistribution::setDegrees(size_t degrees) {
  setShape(degrees * 0.5);
}

size_t ChiSquareDistribution::getDegrees() const {
  return getShape();
}
