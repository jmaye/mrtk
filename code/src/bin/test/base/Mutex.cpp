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

/** \file Mutex.cpp
    \brief This file is a testing binary for the Mutex class
  */

#include <iostream>
#include <stdexcept>

#include "base/Mutex.h"

class M :
  public Mutex {
public:
protected:
  virtual bool safeLock(double wait) throw (InvalidOperationException) {
    std::cout << "Locking mutex" << std::endl;
    return Mutex::safeLock(wait);
  };

  virtual void safeUnlock() throw (InvalidOperationException) {
    Mutex::safeUnlock();
    std::cout << "Unlocked mutex" << std::endl;
  };
};

int main(int argc, char** argv) {
  M mutex;
  mutex.lock();
  mutex.unlock();
  try {
    mutex.unlock();
  }
  catch (std::exception& exception) {
    std::cout << "mutex.unlock(): " << exception.what() << std::endl;
  }
  mutex.lock();
  try {
    mutex.lock();
  }
  catch (std::exception& exception) {
    std::cout << "mutex.lock(): " << exception.what() << std::endl;
  }
  mutex.unlock();
  {
    Mutex::ScopedLock lock(mutex);
  }
  InvalidOperationException e("Test exception");
  try {
    Mutex::ScopedLock lock(mutex);
    throw e;
  }
  catch (std::exception& exception) {
    std::cout << "throw e: " << exception.what() << std::endl;
  }
  return 0;
}
