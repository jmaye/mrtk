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

/** The class Thread implements threading facilities.
    \brief Threading facilities
  */
class Thread {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Thread(const Thread& other);
  /// Assignment operator
  Thread& operator = (const Thread& other);
  /** @}
    */

public:
  /** \name Types definitions
    @{
    */
  /// Thread attribute
  typedef pthread_attr_t Attribute;
  /// Scheduling parameters
  typedef sched_param SchedulingParameter;
  /// Thread state
  enum State {
    initialized,
    starting,
    running,
    sleeping,
    waiting,
    interrupting,
    interrupted,
    finished
  };

  enum Priority {
    inherit,
    idle,
    lowest,
    low,
    normal,
    high,
    highest,
    critical
  };

  struct Identifier :
    public Structure,
    public StructureType<Identifier> {
  public:
    pthread_t posix;
    pid_t kernel;
    pid_t process;

    /** Constructors
      */
    Identifier(pthread_t posix = 0);
    /** Destructor
      */
    virtual ~Identifier();

    /** Thread identifier comparisons
      */
    bool operator==(const Identifier& identifier) const;
    bool operator!=(const Identifier& identifier) const;
    bool operator>(const Identifier& identifier) const;
    bool operator<(const Identifier& identifier) const;

    /** Thread identifier conversions
      */
    operator const void*() const;

    /** Reset the identifier
      */
    void reset();

    void read(InputStream& stream);
    void write(OutputStream& stream) const;
  };

  class BadStackSize :
    public ExceptionType<BadStackSize> {
  public:
    /** Constructors
      */
    BadStackSize();
  };

  class BadWait :
    public ExceptionType<BadWait> {
  public:
    /** Constructors
      */
    BadWait();
  };
  /** @}
    */

  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Thread();
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
  /** \name Protected members
    @{
    */
  /** @}
    */

};

#endif // THREAD_H
