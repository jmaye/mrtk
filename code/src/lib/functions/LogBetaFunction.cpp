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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "functions/LogBetaFunction.h"

#include <cmath>
#include <stdint.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

LogBetaFunction::LogBetaFunction() {
}

LogBetaFunction::~LogBetaFunction() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double LogBetaFunction::operator() (const Eigen::VectorXd& inputVector) {
  double f64Return = 0;
  for (uint32_t i = 0; i < (uint32_t)inputVector.rows(); i++)
    f64Return += lgamma(inputVector(i));
  f64Return -= lgamma(inputVector.sum());
  return f64Return;
}
