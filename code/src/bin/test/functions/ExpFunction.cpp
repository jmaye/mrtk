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

/** \file ExpFunction.cpp
    \brief This file is a testing binary for the ExpFunction class
  */

#include <iostream>
#include <limits>

#include "functions/ExpFunction.h"

int main(int argc, char** argv) {
  ExpFunction<double> e;

  std::cout << "e(0): " << std::fixed << e(0) << std::endl;
  if (fabs(e(0) - 1.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "e(1): " << std::fixed << e(1) << std::endl;
  if (fabs(e(1) - M_E) > std::numeric_limits<double>::epsilon())
    return 1;

  return 0;
}
