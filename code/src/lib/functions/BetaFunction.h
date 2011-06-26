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

/** \file BetaFunction.h
    \brief This file defines the BetaFunction class, which represents the
           beta function
  */

#ifndef BETAFUNCTION_H
#define BETAFUNCTION_H

#include "functions/ContinuousFunction.h"

/** The BetaFunction class represents the beta function
    \brief Beta function
  */
template <typename X, size_t M> class BetaFunction :
  public ContinuousFunction<double, X, M> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  BetaFunction();
  /// Destructor
  virtual ~BetaFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual double getValue(const Eigen::Matrix<X, M, 1>& argument) const;
  /** @}
    */

protected:

};

#include "functions/BetaFunction.tpp"

#endif // BETAFUNCTION_H
