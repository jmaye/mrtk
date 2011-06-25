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

/** The GammaFunction class represents the gamma function
    \brief Gamma function
  */
template <typename X = size_t> class GammaFunction :
  public ContinuousFunction<double, X> {
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
  virtual X getValue(const X& argument) const;
  /** @}
    */

protected:

};

template <> class GammaFunction<size_t> :
  public FactorialFunction,
  public ClassType<GammaFunction<size_t> > {
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
  virtual size_t getValue(const size_t& argument) const;
  /** @}
    */

protected:

};

#include "functions/GammaFunction.tpp"

#endif // GAMMAFUNCTION_H
