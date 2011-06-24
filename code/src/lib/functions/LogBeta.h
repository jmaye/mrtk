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

/** \file LogBeta.h
    \brief This file defines the LogBeta class, which implements the log-beta
           function
  */

#ifndef LOGBETA_H
#define LOGBETA_H

#include "functions/MvContinuousFunction.h"

#include <Eigen/Core>

/** The LogBeta class implements the log-beta function
    \brief Log-beta function
  */
class LogBeta :
  public MvContinuousFunction {

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  LogBeta();
  /// Destructor
  ~LogBeta();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the log-beta function B(inputVector)
  double operator() (const Eigen::VectorXd& inputVector);
  /** @}
    */

protected:

};

#endif // LOGBETA_H
