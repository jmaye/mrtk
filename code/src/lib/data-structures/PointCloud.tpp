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

#include "exceptions/OutOfBoundException.h"
#include "exceptions/IOException.h"
#include "base/BinaryStreamWriter.h"
#include "base/BinaryStreamReader.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X, size_t M>
PointCloud<X, M>::PointCloud() {
}

template <typename X, size_t M>
PointCloud<X, M>::PointCloud(const PointCloud& other) :
  mPoints(other.mPoints) {
}

template <typename X, size_t M>
PointCloud<X, M>& PointCloud<X, M>::operator = (const PointCloud& other) {
  if (this != &other) {
    mPoints = other.mPoints;
  }
  return *this;
}

template <typename X, size_t M>
PointCloud<X, M>::~PointCloud() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename X, size_t M>
void PointCloud<X, M>::read(std::istream& stream) {
}

template <typename X, size_t M>
void PointCloud<X, M>::write(std::ostream& stream) const {
  stream << "points: " << std::endl;
  for (auto it = getPointBegin(); it != getPointEnd(); ++it)
    stream << it->transpose() << std::endl;
}

template <typename X, size_t M>
void PointCloud<X, M>::read(std::ifstream& stream) {
  mPoints.clear();
  if (!stream.is_open())
    throw IOException("PointCloud<X, M>::read(): could not open file");
  while (!stream.eof()) {
    Point point;
    for (size_t i = 0; i < M; ++i) {
      stream >> point(i);
      if (i != M - 1)
        stream.seekg(1, std::ios_base::cur);
    }
    mPoints.push_back(point);
  }
}

template <typename X, size_t M>
void PointCloud<X, M>::write(std::ofstream& stream) const {
  if (!stream.is_open())
    throw IOException("PointCloud<X, M>::write(): could not open file");
  for (auto it = getPointBegin(); it != getPointEnd(); ++it)
    stream << it->transpose() << std::endl;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X, size_t M>
const typename PointCloud<X, M>::Point& PointCloud<X, M>::operator [] (size_t
    idx) const {
  if (!isValidIndex(idx))
    throw OutOfBoundException<size_t>(idx,
      "PointCloud<X, M>::operator []: invalid index", __FILE__, __LINE__);
  return mPoints[idx];
}

template <typename X, size_t M>
typename PointCloud<X, M>::Point& PointCloud<X, M>::operator [] (size_t idx) {
  if (!isValidIndex(idx))
    throw OutOfBoundException<size_t>(idx,
      "PointCloud<X, M>::operator []: invalid index", __FILE__, __LINE__);
  return mPoints[idx];
}

template <typename X, size_t M>
bool PointCloud<X, M>::isValidIndex(size_t idx) const {
  return idx < mPoints.size();
}

template <typename X, size_t M>
size_t PointCloud<X, M>::getNumPoints() const {
  return mPoints.size();
}

template <typename X, size_t M>
void PointCloud<X, M>::clear() {
  mPoints.clear();
}

template <typename X, size_t M>
void PointCloud<X, M>::insertPoint(const Point& point) {
  mPoints.push_back(point);
}

template <typename X, size_t M>
void PointCloud<X, M>::merge(const PointCloud& other) {
  for (auto it = other.getPointBegin(); it != other.getPointEnd(); ++it)
    insertPoint(*it);
}

template <typename X, size_t M>
typename PointCloud<X, M>::ConstPointIterator PointCloud<X, M>::getPointBegin()
    const {
  return mPoints.begin();
}

template <typename X, size_t M>
typename PointCloud<X, M>::PointIterator PointCloud<X, M>::getPointBegin() {
  return mPoints.begin();
}

template <typename X, size_t M>
typename PointCloud<X, M>::ConstPointIterator PointCloud<X, M>::getPointEnd()
    const {
  return mPoints.end();
}

template <typename X, size_t M>
typename PointCloud<X, M>::PointIterator PointCloud<X, M>::getPointEnd() {
  return mPoints.end();
}

template <typename X, size_t M>
const typename PointCloud<X, M>::Container& PointCloud<X, M>::getPoints()
    const {
  return mPoints;
}

template <typename X, size_t M>
void PointCloud<X, M>::reserve(size_t numPoints) {
  mPoints.reserve(numPoints);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename X, size_t M>
void PointCloud<X, M>::writeBinary(std::ostream& stream) const {
  BinaryStreamWriter<std::ostream> binaryStream(stream);
  const size_t numPoints = mPoints.size();
  binaryStream << numPoints;
  for (auto it = getPointBegin(); it != getPointEnd(); ++it)
    for (size_t i = 0; i < M; ++i)
      binaryStream << (*it)(i);
}

template <typename X, size_t M>
void PointCloud<X, M>::readBinary(std::istream& stream) {
  BinaryStreamReader<std::istream> binaryStream(stream);
  size_t numPoints;
  binaryStream >> numPoints;
  for (size_t i = 0; i < numPoints; ++i) {
    Point point;
    for (size_t j = 0; j < M; ++j) {
      X value;
      binaryStream >> value;
      point(j) = value;
    }
    mPoints.push_back(point);
  }
}
