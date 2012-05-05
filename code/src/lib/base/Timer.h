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

/** \file Timer.h
    \brief This file defines the Timer class, which provides timer facilities
  */

#ifndef TIMER_H
#define TIMER_H

#include <pthread.h>

#include "base/Serializable.h"

/** The class Timer implements timer facilities.
    \brief Timer facilities
  */
class Timer :
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
  Timer();
  /// Copy constructor
  Timer(const Timer& other);
  /// Assignment operator
  Timer& operator = (const Timer& other);
  /// Destructor
  virtual ~Timer();
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

#endif // TIMER_H
