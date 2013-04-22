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

/** \file Timer.cpp
    \brief This file is a testing binary for the Timer class
  */

#include <iostream>

#include "base/Timer.h"

int main(int argc, char** argv) {
  Timer timer;
  std::cout << "timer: " << std::endl << timer << std::endl;
  std::cout << "timer.start(): " << std::endl << timer << std::endl;
  timer.start();
  timer.stop(0.1);
  std::cout << "timer.stop(0.1): " << std::endl << timer << std::endl;
  std::cout << "timer.getPeriod(): " << timer.getPeriod() << " s" << std::endl;
  std::cout << "timer.getFrequency(): " << timer.getFrequency() << " Hz"
    << std::endl;
  timer.reset();
  std::cout << "timer.reset(): " << std::endl << timer << std::endl;
  return 0;
}
