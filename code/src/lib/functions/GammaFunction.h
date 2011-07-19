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

/** \file GammaFunction.h
    \brief This file defines the GammaFunction class, which represents the
           gamma function
  */

#ifndef GAMMAFUNCTION_H
#define GAMMAFUNCTION_H

#include "functions/ContinuousFunction.h"
#include "functions/FactorialFunction.h"
#include "exceptions/BadArgumentException.h"

/** The GammaFunction class represents the gamma function for real numbers.
    \brief Gamma function for real numbers
  */
template <typename X = size_t, size_t M = 1> class GammaFunction :
  public ContinuousFunction<double, X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  GammaFunction(const GammaFunction<X, M>& other);
  /// Assignment operator
  GammaFunction& operator = (const GammaFunction<X, M>& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  GammaFunction();
  /// Destructor
  virtual ~GammaFunction();
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

/** The GammaFunction class represents the gamma function for integer numbers.
    \brief Gamma function for integer numbers
  */
template <> class GammaFunction<size_t, 1> :
  public FactorialFunction {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  GammaFunction(const GammaFunction& other);
  /// Assignment operator
  GammaFunction& operator = (const GammaFunction& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  GammaFunction();
  /// Destructor
  virtual ~GammaFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual size_t getValue(const size_t& argument) const
    throw (BadArgumentException<size_t>);
  /** @}
    */

protected:

};

#include "functions/GammaFunction.tpp"

#endif // GAMMAFUNCTION_H
