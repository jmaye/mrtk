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

/** \file KeyPoint.h
    \brief This file defines the class KeyPoint, which represents an interest
           point in an image
  */

#ifndef KEYPOINT_H
#define KEYPOINT_H

#include <iosfwd>

/** The class KeyPoint represents an interest point in an image
    \brief An interest point
  */
class KeyPoint {
  friend std::ostream& operator << (std::ostream& stream, const KeyPoint& obj);
  friend std::istream& operator >> (std::istream& stream, KeyPoint& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const KeyPoint& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, KeyPoint& obj);

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  KeyPoint(const KeyPoint& other);

  /// Assignment operator
  KeyPoint& operator = (const KeyPoint& other);
  /** @}
    */

  /** \name Streaming methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  KeyPoint();
  /// Destructor
  ~KeyPoint();
  /** @}
    */

  /** \name Accessors
    @{
    */

  /** @}
    */

  /** \name Methods
    @{
    */

  /** @}
    */

protected:

};

#endif // KEYPOINT_H
