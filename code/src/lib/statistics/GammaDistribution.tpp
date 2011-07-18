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

GammaDistribution::GammaDistribution(double shape, double scale) {
  setShape(shape);
  setScale(scale);
}

GammaDistribution::GammaDistribution(const GammaDistribution& other) :
  mShape(other.mShape),
  mScale(other.mScale) {
}

GammaDistribution& GammaDistribution::operator =
  (const GammaDistribution& other) {
  mShape = other.mShape;
  mScale = other.mScale;
  return *this;
}

GammaDistribution::~GammaDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GammaDistribution::read(std::istream& stream) {
}

void GammaDistribution::write(std::ostream& stream) const {
  stream << "shape: " << mShape << std::endl
    << "scale: " << mScale;
}

void GammaDistribution::read(std::ifstream& stream) {
}

void GammaDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void GammaDistribution::setShape(double shape)
  throw (BadArgumentException<double>) {
  if (shape <= 0)
    throw BadArgumentException<double>(shape, "GammaDistribution::setShape(): shape must be strictly positive");
  mShape = shape;
  mNormalizer = mShape * log(mScale) + lgamma(mShape);
}

double GammaDistribution::getShape() const {
  return mShape;
}

void GammaDistribution::setScale(double scale)
  throw (BadArgumentException<double>) {
  if (scale <= 0)
    throw BadArgumentException<double>(scale, "GammaDistribution::setScale(): scale must be strictly positive");
  mScale = scale;
  mNormalizer = mShape * log(mScale) + lgamma(mShape);
}

double GammaDistribution::getScale() const {
  return mScale;
}

double GammaDistribution::getNormalizer() const {
  return mNormalizer;
}

double GammaDistribution::pdf(const double& value) const {
  return exp(logpdf(value));
}

double GammaDistribution::logpdf(const double& value) const
  throw (BadArgumentException<double>) {
  if (value < 0)
    throw BadArgumentException<double>(value, "GammaDistribution::logpdf(): value must be positive");
  return (mShape - 1) * log(value) - value / mScale - mNormalizer;
}

double GammaDistribution::getSample() const {
  static Randomizer<double> randomizer;
  return randomizer.sampleGamma(mShape, mScale);
}
