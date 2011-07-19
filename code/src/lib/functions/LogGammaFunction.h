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

/** \file LogGammaFunction.h
    \brief This file defines the LogGammaFunction class, which represents the
           log-gamma function
  */

#ifndef LOGGAMMAFUNCTION_H
#define LOGGAMMAFUNCTION_H

#include "functions/ContinuousFunction.h"
#include "functions/LogFactorialFunction.h"
#include "exceptions/BadArgumentException.h"

/** The LogGammaFunction class represents the log-gamma function for real
    numbers.
    \brief Log-gamma function for real numbers
  */
template <typename X = size_t, size_t M = 1> class LogGammaFunction :
  public ContinuousFunction<double, X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  LogGammaFunction(const LogGammaFunction<X, M>& other);
  /// Assignment operator
  LogGammaFunction& operator = (const LogGammaFunction<X, M>& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  LogGammaFunction();
  /// Destructor
  virtual ~LogGammaFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual double getValue(const X& argument) const;
  /** @}
    */

protected:

};

/** The LogGammaFunction class represents the log-gamma function for integer
    numbers
    \brief Log-gamma function for integer numbers
  */
template <> class LogGammaFunction<size_t, 1> :
  public LogFactorialFunction {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  LogGammaFunction(const LogGammaFunction& other);
  /// Assignment operator
  LogGammaFunction& operator = (const LogGammaFunction& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  LogGammaFunction();
  /// Destructor
  virtual ~LogGammaFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual double getValue(const size_t& argument) const
    throw (BadArgumentException<size_t>);
  /** @}
    */

protected:

};

#include "functions/LogGammaFunction.tpp"

#endif // LOGGAMMAFUNCTION_H
