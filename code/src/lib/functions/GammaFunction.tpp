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
GammaFunction<X, M>::GammaFunction() {
}

GammaFunction<size_t, 1>::GammaFunction() {
}

template <typename X, size_t M>
GammaFunction<X, M>::~GammaFunction() {
}

GammaFunction<size_t, 1>::~GammaFunction() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X, size_t M>
double GammaFunction<X, M>::getValue(const X& argument) const {
  double prod = 1.0;
  for (size_t i = 0; i < M; ++i) {
    prod *= tgamma(argument - 0.5 * i);
  }
  return prod * pow(M_PI, M * (M - 1) * 0.25);
}

size_t GammaFunction<size_t, 1>::getValue(const size_t& argument) const
  throw (BadArgumentException<size_t>) {
  if (argument)
    return FactorialFunction::getValue(argument - 1);
  else throw BadArgumentException<size_t>(argument,
  "GammaFunction<size_t>::getValue(): argument must be strictly positive",
  __FILE__, __LINE__);
}
