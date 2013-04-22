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

/** \file Histogram.cpp
    \brief This file is a testing binary for the Histogram class
  */

#include <iostream>
#include <limits>

#include "statistics/Histogram.h"

int main(int argc, char** argv) {
  std::cout << "Testing discrete histograms 1-D" << std::endl;
  Histogram<size_t, 1> hist1Disc(0, 10, 1);

  std::cout << "Adding sample 0" << std::endl;
  hist1Disc.addSample(0);
  std::cout << "Adding sample 2" << std::endl;
  hist1Disc.addSample(2);
  std::cout << "Adding sample 3" << std::endl;
  hist1Disc.addSample(3);

  std::cout << "hist.getMean(): " << std::endl << hist1Disc.getMean()
    << std::endl << std::endl;
  std::cout << "hist.getMode(): " << std::endl << hist1Disc.getMode()
    << std::endl << std::endl;
  std::cout << "hist.getVariance(): " << std::endl <<
    hist1Disc.getVariance() << std::endl << std::endl;

  std::cout << "hist.getNormalized():" << std::endl <<
    hist1Disc.getNormalized() << std::endl;

  Histogram<size_t, 1> hist1Copy(hist1Disc);
  std::cout << "Copy constructor: " << std::endl << hist1Copy << std::endl
    << std::endl;
  Histogram<size_t, 1> hist1Assign = hist1Disc;
  std::cout << "Assignment operator: " << std::endl << hist1Assign << std::endl;

  std::cout << std::endl;

  std::cout << "Testing continuous histograms 1-D" << std::endl;
  Histogram<double, 1> hist1Cont(0, 10, 1);

  std::cout << "Adding sample 0" << std::endl;
  hist1Cont.addSample(0);
  std::cout << "Adding sample 2" << std::endl;
  hist1Cont.addSample(2);
  std::cout << "Adding sample 3" << std::endl;
  hist1Cont.addSample(3);

  std::cout << "hist.getMean(): " << std::endl << hist1Cont.getMean()
    << std::endl << std::endl;
  std::cout << "hist.getMode(): " << std::endl << hist1Cont.getMode()
    << std::endl << std::endl;
  std::cout << "hist.getVariance(): " << std::endl <<
    hist1Cont.getVariance() << std::endl << std::endl;

  std::cout << "hist.getNormalized():" << std::endl <<
    hist1Cont.getNormalized() << std::endl;

  Histogram<double, 1> hist1Copyd(hist1Cont);
  std::cout << "Copy constructor: " << std::endl << hist1Copyd << std::endl
    << std::endl;
  Histogram<double, 1> hist1Assignd = hist1Cont;
  std::cout << "Assignment operator: " << std::endl << hist1Assignd
    << std::endl;

  std::cout << std::endl;

  std::cout << "Testing continuous histograms 3-D" << std::endl;
  Histogram<double, 3> hist3Cont(Eigen::Matrix<double, 3, 1>(0, 0, 0),
    Eigen::Matrix<double, 3, 1>(3, 3, 3),
    Eigen::Matrix<double, 3, 1>(1.0, 1.0, 1.0));

  std::cout << "Adding sample (1.5, 1.5, 1.5)" << std::endl;
  hist3Cont.addSample(Eigen::Matrix<double, 3, 1>(1.5, 2.0, 1.5));
  std::cout << "Adding sample (2.0, 2.0, 2.0)" << std::endl;
  hist3Cont.addSample(Eigen::Matrix<double, 3, 1>(2.0, 1.5, 2.0));
  std::cout << "Adding sample (2.5, 2.5, 2.5)" << std::endl;
  hist3Cont.addSample(Eigen::Matrix<double, 3, 1>(2.5, 2.0, 2.5));

  std::cout << "hist.getMean(): " << std::endl << hist3Cont.getMean()
    << std::endl << std::endl;
  std::cout << "hist.getMode(): " << std::endl << hist3Cont.getMode()
    << std::endl << std::endl;
  std::cout << "hist.getCovariance(): " << std::endl <<
    hist3Cont.getCovariance() << std::endl << std::endl;

  std::cout << "hist.getNormalized():" << std::endl <<
    hist3Cont.getNormalized() << std::endl;

  Histogram<double, 3> histCopy(hist3Cont);
  std::cout << "Copy constructor: " << std::endl << histCopy << std::endl
    << std::endl;
  Histogram<double, 3> histAssign = hist3Cont;
  std::cout << "Assignment operator: " << std::endl << histAssign << std::endl;

  return 0;
}
