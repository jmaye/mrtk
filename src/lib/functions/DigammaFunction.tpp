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

#include <gsl/gsl_sf_psi.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X>
DigammaFunction<X>::DigammaFunction() {
}

DigammaFunction<size_t>::DigammaFunction() {
}

template <typename X>
DigammaFunction<X>::~DigammaFunction() {
}

DigammaFunction<size_t>::~DigammaFunction() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X>
double DigammaFunction<X>::getValue(const VariableType& argument) const {
  return gsl_sf_psi(argument);
}

double DigammaFunction<size_t>::getValue(const VariableType& argument) const {
  return gsl_sf_psi_int(argument);
}
