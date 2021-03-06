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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X, size_t M, size_t N>
DiscreteDistribution<X, M, N>::DiscreteDistribution() {
}

template <typename X, size_t M, size_t N>
DiscreteDistribution<X, M, N>::~DiscreteDistribution() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X, size_t M, size_t N>
double DiscreteDistribution<X, M, N>::getValue(const Eigen::Matrix<X, M, N>&
    argument) const {
  return pmf(argument);
}
