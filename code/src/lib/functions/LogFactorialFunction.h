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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file LogFactorialFunction.h
    \brief This file defines the LogFactorialFunction class, which implements
           the log-factorial function
  */

#ifndef LOGFACTORIALFUNCTION_H
#define LOGFACTORIALFUNCTION_H

#include "functions/DiscreteFunction.h"

#include <stdint.h>

/** The LogFactorialFunction class implements the log-factorial function
    \brief Log-factorial function
  */
class LogFactorialFunction {

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  LogFactorialFunction();
  /// Destructor
  ~LogFactorialFunction();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the log-factorial of a number
  double operator() (uint32_t u32N);
  /** @}
    */

protected:

};

#endif // LOGFACTORIALFUNCTION_H
