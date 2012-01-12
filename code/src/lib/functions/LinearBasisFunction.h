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

/** \file LinearBasisFunction.h
    \brief This file defines the LinearBasisFunction class, which represents a
           linear basis function model
  */

#ifndef LINEARBASISFUNCTION_H
#define LINEARBASISFUNCTION_H

#include "functions/ContinuousFunction.h"

/** The LinearBasisFunction class represents the linear basis function model.
    \brief Linear basis function model
  */
template <typename X, size_t M> class LinearBasisFunction :
  public ContinuousFunction<double, X, M> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  LinearBasisFunction(const LinearBasisFunction<X, M>& other);
  /// Assignment operator
  LinearBasisFunction& operator = (const LinearBasisFunction<X, M>& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructors with the linear coefficients
  LinearBasisFunction(const Eigen::Matrix<X, M, 1>& coefficients);
  /// Destructor
  virtual ~LinearBasisFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the linear coefficients
  const Eigen::Matrix<X, M, 1>& getCoefficients() const;
  /// Sets the linear coefficients
  void setCoefficients(const Eigen::Matrix<X, M, 1>& coefficients);
  /// Access the function value for the given argument
  virtual double getValue(const Eigen::Matrix<X, M, 1>& argument) const;
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Linear coefficients
  Eigen::Matrix<X, M, 1> mCoefficients;
  /** @}
    */

};

#include "functions/LinearBasisFunction.tpp"

#endif // LINEARBASISFUNCTION_H
