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

/** \file Binomial.h
    \brief This file defines the Binomial class, which implements the binomial
           function
  */

#ifndef BINOMIAL_H
#define BINOMIAL_H

#include "functions/MvDiscreteFunction.h"

#include <stdint.h>

/** The Binomial class implements the binomial function
    \brief Binomial function
  */
class Binomial :
  public MvDiscreteFunction {

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Binomial();
  /// Destructor
  ~Binomial();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the binomial of (N, K)
  uint32_t operator() (uint32_t u32N, uint32_t u32K);
  /** @}
    */

protected:

};

#endif // BINOMIAL_H
