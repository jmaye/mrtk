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

/** \file Colors.h
    \brief This file defines the color utilities.
  */

#ifndef COLORS_H
#define COLORS_H

#include <cstdlib>

/** The Color class contains utilities for managing colors.
    \brief Color utilities
  */
namespace Colors {
  /** \name Types definitions
    @{
    */
  /// Color type
  struct Color {
    /// Red component
    double mRed;
    /// Green component
    double mGreen;
    /// Blue component
    double mBlue;
  };
  /** @}
    */

  /** The revertBits function reverts the bits of the input
  */
  template <typename T>
  static T revertBits(T value);

  /** The intToHue function generates a hue value from an index
  */
  template <typename T = size_t>
  static double intToHue(T value);

  /** The genColor function generates a color from an index.
  */
  static Color genColor(size_t idx);
};

#include "utils/Colors.tpp"

#endif // COLORS_H
