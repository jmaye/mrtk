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

/** \file Image.h
    \brief This file defines the class Image, which represents an image
  */

#ifndef IMAGE_H
#define IMAGE_H

#include <iosfwd>

/** The class Image represents an image
    \brief An image
  */
class Image {
  friend std::ostream& operator << (std::ostream& stream, const Image& obj);
  friend std::istream& operator >> (std::istream& stream, Image& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const Image& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Image& obj);

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Image(const Image& other);
  /// Assignment operator
  Image& operator = (const Image& other);
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
  Image();
  /// Destructor
  ~Image();
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

#endif // IMAGE_H
