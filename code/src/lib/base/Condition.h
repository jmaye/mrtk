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

/** \file Condition.h
    \brief This file defines the Condition class, which provides condition
           facilities
  */

#ifndef CONDITION_H
#define CONDITION_H

#include <pthread.h>

#include "base/Serializable.h"

/** The class Condition implements condition facilities.
    \brief Condition facilities
  */
class Condition :
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
  Condition();
  /// Copy constructor
  Condition(const Condition& other);
  /// Assignment operator
  Condition& operator = (const Condition& other);
  /// Destructor
  virtual ~Condition();
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

#endif // CONDITION_H
