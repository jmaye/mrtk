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

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X, size_t M>
LogGammaFunction<X, M>::LogGammaFunction() {
}

LogGammaFunction<size_t, 1>::LogGammaFunction() {
}

template <typename X, size_t M>
LogGammaFunction<X, M>::~LogGammaFunction() {
}

LogGammaFunction<size_t, 1>::~LogGammaFunction() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X, size_t M>
double LogGammaFunction<X, M>::getValue(const X& argument) const {
  double sum = 0.0;
  for (size_t i = 0; i < M; ++i) {
    sum += lgamma(argument - 0.5 * i);
  }
  return sum + M * (M - 1) * 0.25 * log(M_PI);
}

double LogGammaFunction<size_t, 1>::getValue(const size_t& argument) const
  throw (BadArgumentException<size_t>) {
  if (argument)
    return LogFactorialFunction::getValue(argument - 1);
  else throw BadArgumentException<size_t>(argument, "LogGammaFunction<size_t>::getValue(): argument must be strictly positive");
}
