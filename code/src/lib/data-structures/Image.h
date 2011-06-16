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
  */

#ifndef IMAGE_H
#define IMAGE_H

#include <iosfwd>

/**
  */
class Image {
  friend std::ostream& operator << (std::ostream& stream, const Image& obj);
  friend std::istream& operator >> (std::istream& stream, Image& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const Image& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Image& obj);

  /** Copy constructor
    */
  Image(const Image& other);

  /** Assignment operator
    */
  Image& operator = (const Image& other);

  /** Stream methods
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  /** Constructors
    */
  Image();

  /** Destructor
    */
  ~Image();

  /** Accessors
    */

protected:

};

#endif // IMAGE_H
