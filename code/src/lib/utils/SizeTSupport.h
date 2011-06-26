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

/** \file SizeTSupport.h
    \brief This file defines the Eigen support for size_t type
  */

#ifndef SIZETSUPPORT_H
#define SIZETSUPPORT_H

#include <Eigen/Core>

#include <cstdlib>

namespace Eigen {

template<> struct NumTraits<size_t>
{
  typedef size_t Real;
  typedef double FloatingPoint;
  enum {
    IsComplex = 0,
    HasFloatingPoint = 0,
    ReadCost = 1,
    AddCost = 1,
    MulCost = 1,
  };
};

}

#endif // SIZETSUPPORT_H
