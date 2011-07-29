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

/** \file LogisticFunction.cpp
    \brief This file is a testing binary for the LogisticFunction class
  */

#include "functions/LogisticFunction.h"

#include <iostream>
#include <limits>

int main(int argc, char** argv) {
  LogisticFunction<double> l;

  std::cout << "l(0): " << std::fixed << l(0) << std::endl;
  if (fabs(l(0) - 0.5) > std::numeric_limits<double>::epsilon())
    return 1;

  return 0;
}
