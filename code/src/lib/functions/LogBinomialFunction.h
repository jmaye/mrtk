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

/** \file LogBinomialFunction.h
    \brief This file defines the LogBinomialFunction class, which implements the
           log-binomial function
  */

#ifndef LOGBINOMIALFUNCTION_H
#define LOGBINOMIALFUNCTION_H

#include <stdint.h>

/** The LogBinomialFunction class implements the log-binomial function
    \brief Log-binomial function
  */
class LogBinomialFunction {

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  LogBinomialFunction();
  /// Destructor
  ~LogBinomialFunction();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the log-binomial of (N, K)
  double operator() (uint32_t u32N, uint32_t u32K);
  /** @}
    */

protected:

};

#endif // LOGBINOMIAL_H
