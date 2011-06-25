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

#include "functions/LogBinomialFunction.h"

#include "functions/LogFactorialFunction.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

LogBinomialFunction::LogBinomialFunction() {
}

LogBinomialFunction::~LogBinomialFunction() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double LogBinomialFunction::operator() (uint32_t u32N, uint32_t u32K) {
  LogFactorialFunction logFactorialFunction;
  return logFactorialFunction(u32N) - (logFactorialFunction(u32K) +
    logFactorialFunction(u32N - u32K));
}
