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

#include "functions/LogGammaFunction.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T>
GammaDistribution<T>::GammaDistribution(const T& shape, double scale) {
  setShape(shape);
  setScale(scale);
}

template <typename T>
GammaDistribution<T>::GammaDistribution(const GammaDistribution<T>& other) :
  mShape(other.mShape),
  mScale(other.mScale) {
}

template <typename T>
GammaDistribution<T>& GammaDistribution<T>::operator =
  (const GammaDistribution<T>& other) {
  mShape = other.mShape;
  mScale = other.mScale;
  return *this;
}

template <typename T>
GammaDistribution<T>::~GammaDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T>
void GammaDistribution<T>::read(std::istream& stream) {
}

template <typename T>
void GammaDistribution<T>::write(std::ostream& stream) const {
  stream << "shape: " << mShape << std::endl
    << "scale: " << mScale;
}

template <typename T>
void GammaDistribution<T>::read(std::ifstream& stream) {
}

template <typename T>
void GammaDistribution<T>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T>
void GammaDistribution<T>::setShape(const T& shape)
  throw (BadArgumentException<T>) {
  if (shape <= 0)
    throw BadArgumentException<T>(shape, "GammaDistribution::setShape(): shape must be strictly positive");
  mShape = shape;
  LogGammaFunction<T> logGammaFunction;
  mNormalizer = mShape * log(mScale) + logGammaFunction(mShape);
}

template <typename T>
const T& GammaDistribution<T>::getShape() const {
  return mShape;
}

template <typename T>
void GammaDistribution<T>::setScale(double scale)
  throw (BadArgumentException<double>) {
  if (scale <= 0)
    throw BadArgumentException<double>(scale, "GammaDistribution::setScale(): scale must be strictly positive");
  mScale = scale;
  LogGammaFunction<T> logGammaFunction;
  mNormalizer = mShape * log(mScale) + logGammaFunction(mShape);
}

template <typename T>
double GammaDistribution<T>::getScale() const {
  return mScale;
}

template <typename T>
double GammaDistribution<T>::getNormalizer() const {
  return mNormalizer;
}

template <typename T>
double GammaDistribution<T>::pdf(const double& value) const {
  if (value <= 0)
    return 0.0;
  else
    return exp(logpdf(value));
}

template <typename T>
double GammaDistribution<T>::logpdf(const double& value) const {
  return (mShape - 1) * log(value) - value / mScale - mNormalizer;
}

template <typename T>
double GammaDistribution<T>::getSample() const {
  static Randomizer<double> randomizer;
  return randomizer.sampleGamma(mShape, mScale);
}
