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

/** \file Thread.h
    \brief This file defines the Thread class, which provides threading
           facilities
  */

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

#include "base/Serializable.h"

/** The class Thread implements threading facilities.
    \brief Threading facilities
  */
class Thread :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  typedef pthread_attr_t Attribute;
  typedef sched_param SchedulingParameter;
  /** @}
    */

  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Thread();
  /// Copy constructor
  Thread(const Thread& other);
  /// Assignment operator
  Thread& operator = (const Thread& other);
  /// Destructor
  virtual ~Thread();
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

#endif // THREAD_H
