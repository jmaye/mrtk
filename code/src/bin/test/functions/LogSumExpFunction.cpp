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

/** \file LogSumExpFunction.cpp
    \brief This file is a testing binary for the LogSumExpFunction class
  */

#include <iostream>
#include <limits>

#include "functions/LogSumExpFunction.h"

int main(int argc, char** argv) {
  LogSumExpFunction<double, 3> lse;
  Eigen::Matrix<double, 3, 1> logProb(log(1.0), log(0.4), log(0.6));
  std::cout << "lse(log(1.0), log(0.4), log(0.6)): " << lse(logProb)
    << std::endl;
  std::cout << "normalized log-probabilities: " << std::endl
    << logProb.cwise() - lse(logProb) << std::endl;
  std::cout << "normalized probabilities: " << std::endl
    << (logProb.cwise() - lse(logProb)).cwise().exp() << std::endl;
  if (fabs((logProb.cwise() - lse(logProb)).cwise().exp().sum() - 1.0) >
      std::numeric_limits<double>::epsilon())
    return 1;
  return 0;
}
