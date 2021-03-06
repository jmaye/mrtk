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

/** \file Timestamp.cpp
    \brief This file is a testing binary for the Timestamp class
  */

#include <iostream>

#include "base/Timestamp.h"

int main(int argc, char** argv) {
  Timestamp time;
  std::cout << "time: " << std::endl << time << std::endl;
  std::cout << "Timestamp::now(): " << std::fixed << Timestamp::now()
    << std::endl;
  std::cout << "Timestamp::getDate(): " << std::fixed << Timestamp::getDate()
    << std::endl;
  return 0;
}
