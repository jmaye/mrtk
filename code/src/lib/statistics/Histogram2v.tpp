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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T>
Histogram<T, 2>::Histogram() {
}

template <typename T>
Histogram<T, 2>::Histogram(const Histogram<T, 2>& other) {
}

template <typename T>
Histogram<T, 2>& Histogram<T, 2>::operator =
  (const Histogram<T, 2>& other) {
  if (this != &other) {
  }
  return *this;
}

template <typename T>
Histogram<T, 2>::~Histogram() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T>
void Histogram<T, 2>::read(std::istream& stream) {
}

template <typename T>
void Histogram<T, 2>::write(std::ostream& stream) const {
}

template <typename T>
void Histogram<T, 2>::read(std::ifstream& stream) {
}

template <typename T>
void Histogram<T, 2>::write(std::ofstream& stream) const {
}
