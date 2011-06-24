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

/** \file Beta.h
    \brief This file defines the Beta class, which implements the beta function
  */

#ifndef BETA_H
#define BETA_H

#include "functions/MvContinuousFunction.h"

#include <Eigen/Core>

/** The Beta class implements the beta function
    \brief Beta function
  */
class Beta :
  public MvContinuousFunction {

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Beta();
  /// Destructor
  ~Beta();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the beta function B(inputVector)
  double operator() (const Eigen::VectorXd& inputVector);
  /** @}
    */

protected:

};

#endif // BETA_H
