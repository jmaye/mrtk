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

/** \file Thread.cpp
    \brief This file is a testing binary for the Thread class
  */

#include <iostream>

#include "base/Threads.h"

class T :
  public Thread {
public:
  T(int id, double cycle, bool exit = false) :
      Thread(cycle),
      id(id),
      exit(exit) {
  };
  virtual ~T() {
  };
protected:
  int id;
  bool exit;
  virtual void process() {
    printf("Thread %d CYCLE\n", id);
    if (exit) Thread::exit();
  };
  State safeSetState(State state) {
    State oldState = Thread::safeSetState(state);
    printf("Thread %d %d\n", id, this->mState);
    return oldState;
  };
};

int main(int argc, char** argv) {
  T t_1(1, 0.1);
  T t_2(2, 0.02);
  t_1.start();
  t_2.start();
  Timer::sleep(0.1);
  t_1.interrupt();
  Threads::getInstance().interrupt();
  T t_3(3, 0.0);
  t_3.start();
  t_3.wait();
  T t_4(4, 0.1, true);
  t_4.start();
  t_4.wait();
  return 0;
}
