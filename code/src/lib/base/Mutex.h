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

/** \file Mutex.h
    \brief This file defines the Mutex class, which provides mutex facilities
  */

#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

#include "base/Serializable.h"

/** The class Mutex implements mutex facilities.
    \brief Mutex facilities
  */
class Mutex :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /** @}
    */

  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Mutex();
  /// Copy constructor
  Mutex(const Mutex& other);
  /// Assignment operator
  Mutex& operator = (const Mutex& other);
  /// Destructor
  virtual ~Mutex();
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
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /** @}
    */

};

#endif // MUTEX_H
