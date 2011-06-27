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
    \brief This file defines the LogFactorialFunction class, which represents
           the log-factorial function
  */

#ifndef LOGFACTORIALFUNCTION_H
#define LOGFACTORIALFUNCTION_H

#include "functions/DiscreteFunction.h"

/** The LogFactorialFunction class represents the log-factorial function
    \brief Log-factorial function
  */
class LogFactorialFunction :
  public DiscreteFunction<double, size_t> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  LogFactorialFunction();
  /// Destructor
  virtual ~LogFactorialFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual double getValue(const size_t& argument) const;
  /** @}
    */

protected:

};

#include "functions/LogFactorialFunction.tpp"

#endif // LOGFACTORIALFUNCTION_H
