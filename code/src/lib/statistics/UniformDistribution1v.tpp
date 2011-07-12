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

template <typename X>
UniformDistribution<X>::UniformDistribution(const X& minSupport,
  const X& maxSupport) {
  setSupport(minSupport, maxSupport);
}

UniformDistribution<ssize_t>::UniformDistribution(const ssize_t& minSupport,
  const ssize_t& maxSupport) {
  setSupport(minSupport, maxSupport);
}

template <typename X>
UniformDistribution<X>::UniformDistribution(const UniformDistribution<X>&
  other) :
  mMinSupport(other.mMinSupport),
  mMaxSupport(other.mMaxSupport) {
}

UniformDistribution<ssize_t>::UniformDistribution(const
  UniformDistribution<ssize_t>& other) :
  mMinSupport(other.mMinSupport),
  mMaxSupport(other.mMaxSupport) {
}

template <typename X>
UniformDistribution<X>& UniformDistribution<X>::operator =
  (const UniformDistribution<X>& other) {
  mMaxSupport = other.mMaxSupport;
  mMinSupport = other.mMinSupport;
  return *this;
}

UniformDistribution<ssize_t>& UniformDistribution<ssize_t>::operator =
  (const UniformDistribution<ssize_t>& other) {
  mMaxSupport = other.mMaxSupport;
  mMinSupport = other.mMinSupport;
  return *this;
}

template <typename X>
UniformDistribution<X>::~UniformDistribution() {
}

UniformDistribution<ssize_t>::~UniformDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename X>
void UniformDistribution<X>::read(std::istream& stream) {
}

void UniformDistribution<ssize_t>::read(std::istream& stream) {
}

template <typename X>
void UniformDistribution<X>::write(std::ostream& stream) const {
  stream << "minimum support: " << mMinSupport << std::endl
    << "maximum support: " << mMaxSupport;
}

void UniformDistribution<ssize_t>::write(std::ostream& stream) const {
  stream << "minimum support: " << mMinSupport << std::endl
    << "maximum support: " << mMaxSupport;
}

template <typename X>
void UniformDistribution<X>::read(std::ifstream& stream) {
}

void UniformDistribution<ssize_t>::read(std::ifstream& stream) {
}

template <typename X>
void UniformDistribution<X>::write(std::ofstream& stream) const {
}

void UniformDistribution<ssize_t>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X>
void UniformDistribution<X>::setSupport(const X& minSupport, const X&
  maxSupport) throw (BadArgumentException<X>) {
  if (minSupport >= maxSupport)
    throw BadArgumentException<X>(minSupport, "UniformDistribution<X>::setSupport(): minimum support must be smaller than maximum support");
  mMinSupport = minSupport;
  mMaxSupport = maxSupport;
}

void UniformDistribution<ssize_t>::setSupport(const ssize_t& minSupport, const
  ssize_t& maxSupport) throw (BadArgumentException<ssize_t>) {
  if (minSupport >= maxSupport)
    throw BadArgumentException<ssize_t>(minSupport, "UniformDistribution<ssize_t>::setSupport(): minimum support must be smaller than maximum support");
  mMinSupport = minSupport;
  mMaxSupport = maxSupport;
}

template <typename X>
void UniformDistribution<X>::setMinSupport(const X& minSupport) {
  setSupport(minSupport, mMaxSupport);
}

void UniformDistribution<ssize_t>::setMinSupport(const ssize_t& minSupport) {
  setSupport(minSupport, mMaxSupport);
}

template <typename X>
const X& UniformDistribution<X>::getMinSupport() const {
  return mMinSupport;
}

const ssize_t& UniformDistribution<ssize_t>::getMinSupport() const {
  return mMinSupport;
}

template <typename X>
void UniformDistribution<X>::setMaxSupport(const X& maxSupport) {
  setSupport(mMinSupport, maxSupport);
}

void UniformDistribution<ssize_t>::setMaxSupport(const ssize_t& maxSupport) {
  setSupport(mMinSupport, maxSupport);
}

template <typename X>
const X& UniformDistribution<X>::getMaxSupport() const {
  return mMaxSupport;
}

const ssize_t& UniformDistribution<ssize_t>::getMaxSupport() const {
  return mMaxSupport;
}

template <typename X>
double UniformDistribution<X>::pdf(const X& value) const {
  if (value >= mMinSupport && value <= mMaxSupport)
    return 1.0 / (mMaxSupport - mMinSupport);
  else
    return 0.0;
}

double UniformDistribution<ssize_t>::pmf(const ssize_t& value) const {
  if (value >= mMinSupport && value <= mMaxSupport)
    return 1.0 / (mMaxSupport - mMinSupport + 1);
  else
    return 0.0;
}

template <typename X>
X UniformDistribution<X>::getSample() const {
  return X(0.0);
}

ssize_t UniformDistribution<ssize_t>::getSample() const {
  return 0.0;
}
