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

/** \file UniformDistribution.cpp
    \brief This file is a testing binary for the UniformDistribution class
  */

#include <iostream>
#include <limits>

#include "statistics/UniformDistribution.h"

int main(int argc, char** argv) {
  std::cout << "Testing continuous uniform distribution 1-D" << std::endl;
  UniformDistribution<double> distCont;
  std::cout << "Distribution default parameters: " << std::endl << distCont
    << std::endl << std::endl;

  std::cout << "dist.getMinSupport(): " << distCont.getMinSupport() << std::endl
    << std::endl;
  std::cout << "dist.getMaxSupport(): " << distCont.getMaxSupport() << std::endl
    << std::endl;

  std::cout << "dist.setSupport(2, 5)" << std::endl << std::endl;
  distCont.setSupport(2, 5);
  std::cout << "Distribution new parameters: " << std::endl << distCont
    << std::endl << std::endl;
  if (distCont.getMinSupport() != 2)
    return 1;
  if (distCont.getMaxSupport() != 5)
    return 1;

  std::cout << "pdf(2): " << std::fixed << distCont(2) << std::endl
    << std::endl;
  if (fabs(distCont(2) - 1.0 / 3.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf(5): " << std::fixed << distCont(5) << std::endl
    << std::endl;
  if (fabs(distCont(5) -  1.0 / 3.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf(3): " << std::fixed << distCont(3) << std::endl
    << std::endl;
  if (fabs(distCont(3) -  1.0 / 3.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf(10): " << std::fixed << distCont(10) << std::endl
    << std::endl;
  if (fabs(distCont(10) - 0.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "dist.getMean(): " << std::fixed << distCont.getMean()
    << std::endl << std::endl;
  if (fabs(distCont.getMean() - 1.5) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed << distCont.getVariance()
    << std::endl << std::endl;
  if (fabs(distCont.getVariance() - 9.0 / 12.0) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMode(): " << std::fixed << distCont.getMode()
    << std::endl << std::endl;
  if (fabs(distCont.getMode() - 2) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMedian(): " << std::fixed << distCont.getMedian()
    << std::endl << std::endl;
  if (fabs(distCont.getMedian() - 1.5) > std::numeric_limits<double>::epsilon())
    return 1;

  try {
    std::cout << "dist.setSupport(5, 2)" << std::endl;
    distCont.setSupport(5, 2);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "dist.getSample(): " << std::endl << distCont.getSample()
    << std::endl << std::endl;
  std::vector<double> samples;
  distCont.getSamples(samples, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples[i] << std::endl;
  std::cout << std::endl;

  UniformDistribution<double> distCopy(distCont);
  std::cout << "Copy constructor: " << std::endl << distCopy << std::endl
    << std::endl;
  if (distCopy.getMaxSupport() != distCont.getMaxSupport())
    return 1;
  if (distCopy.getMinSupport() != distCont.getMinSupport())
    return 1;
  UniformDistribution<double> distAssign = distCont;
  std::cout << "Assignment operator: " << std::endl << distAssign << std::endl;
  if (distAssign.getMaxSupport() != distCont.getMaxSupport())
    return 1;
  if (distAssign.getMinSupport() != distCont.getMinSupport())
    return 1;

  std::cout << std::endl;

  std::cout << "Testing discrete uniform distribution 1-D" << std::endl;
  UniformDistribution<size_t> distDisc;
  std::cout << "Distribution default parameters: " << std::endl << distDisc
    << std::endl << std::endl;

  std::cout << "dist.getMinSupport(): " << distDisc.getMinSupport() << std::endl
    << std::endl;
  std::cout << "dist.getMaxSupport(): " << distDisc.getMaxSupport() << std::endl
    << std::endl;

  std::cout << "dist.setSupport(2, 5)" << std::endl << std::endl;
  distDisc.setSupport(2, 5);
  std::cout << "Distribution new parameters: " << std::endl << distDisc
    << std::endl << std::endl;
  if (distDisc.getMinSupport() != 2)
    return 1;
  if (distDisc.getMaxSupport() != 5)
    return 1;

  std::cout << "pdf(2): " << std::fixed << distDisc(2) << std::endl
    << std::endl;
  if (fabs(distDisc(2) - 1.0 / 4.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf(5): " << std::fixed << distDisc(5) << std::endl
    << std::endl;
  if (fabs(distDisc(5) -  1.0 / 4.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf(3): " << std::fixed << distDisc(3) << std::endl
    << std::endl;
  if (fabs(distDisc(3) -  1.0 / 4.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf(10): " << std::fixed << distDisc(10) << std::endl
    << std::endl;
  if (fabs(distDisc(10) - 0.0) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "dist.getMean(): " << std::fixed << distDisc.getMean()
    << std::endl << std::endl;
  if (fabs(distDisc.getMean() - 1.5) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getVariance(): " << std::fixed << distDisc.getVariance()
    << std::endl << std::endl;
  if (fabs(distDisc.getVariance() - 15.0 / 12.0) >
      std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMode(): " << std::fixed << distDisc.getMode()
    << std::endl << std::endl;
  if (fabs(distDisc.getMode() - 2) > std::numeric_limits<double>::epsilon())
    return 1;
  std::cout << "dist.getMedian(): " << std::fixed << distDisc.getMedian()
    << std::endl << std::endl;
  if (fabs(distDisc.getMedian() - 1.5) > std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "dist.getSample(): " << std::endl << distDisc.getSample()
    << std::endl << std::endl;
  std::vector<size_t> samplesDisc;
  distDisc.getSamples(samplesDisc, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samplesDisc[i] << std::endl;
  std::cout << std::endl;

  std::cout << "Testing continuous uniform distribution 2-D" << std::endl;
  UniformDistribution<double, 2> distCont2D;
  std::cout << "Distribution default parameters: " << std::endl << distCont2D
    << std::endl << std::endl;

  std::cout << "dist.getMinSupport(): " << distCont2D.getMinSupport()
    << std::endl << std::endl;
  std::cout << "dist.getMaxSupport(): " << distCont2D.getMaxSupport()
    << std::endl << std::endl;

  std::cout << "dist.setSupport((2, 2), (5, 5))" << std::endl << std::endl;
  distCont2D.setSupport(Eigen::Matrix<double, 2, 1>(2, 2),
    Eigen::Matrix<double, 2, 1>(5, 5));
  std::cout << "Distribution new parameters: " << std::endl << distCont2D
    << std::endl << std::endl;

  std::cout << "pdf((2, 2)): " << std::fixed
    << distCont2D(Eigen::Matrix<double, 2, 1>(2, 2)) << std::endl << std::endl;
  if (fabs(distCont2D(Eigen::Matrix<double, 2, 1>(2, 2)) - 1.0 / 9.0) >
      std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf((5, 5)): " << std::fixed
    << distCont2D(Eigen::Matrix<double, 2, 1>(5, 5)) << std::endl << std::endl;
  if (fabs(distCont2D(Eigen::Matrix<double, 2, 1>(5, 5)) -  1.0 / 9.0) >
      std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf((3, 3)): " << std::fixed
    << distCont2D(Eigen::Matrix<double, 2, 1>(3, 3)) << std::endl << std::endl;
  if (fabs(distCont2D(Eigen::Matrix<double, 2, 1>(3, 3)) -  1.0 / 9.0) >
      std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf((10, 10)): " << std::fixed
    << distCont2D(Eigen::Matrix<double, 2, 1>(10, 10)) << std::endl
    << std::endl;
  if (fabs(distCont2D(Eigen::Matrix<double, 2, 1>(10, 10)) - 0.0) >
      std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "dist.getSample(): " << std::endl << distCont2D.getSample()
    << std::endl << std::endl;

  try {
    distCont2D.setSupport(Eigen::Matrix<double, 2, 1>(5, 2),
    Eigen::Matrix<double, 2, 1>(2, 5));
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << std::endl;

  std::cout << "Testing discrete uniform distribution 2-D" << std::endl;
  UniformDistribution<int, 2> distDisc2D;
  std::cout << "Distribution default parameters: " << std::endl << distDisc2D
    << std::endl << std::endl;
  std::cout << "dist.getMinSupport(): " << distDisc2D.getMinSupport()
    << std::endl << std::endl;
  std::cout << "dist.getMaxSupport(): " << distDisc2D.getMaxSupport()
    << std::endl << std::endl;
  std::cout << "dist.setSupport((2, 2), (5, 5))" << std::endl << std::endl;
  distDisc2D.setSupport(Eigen::Matrix<int, 2, 1>(2, 2),
    Eigen::Matrix<int, 2, 1>(5, 5));
  std::cout << "Distribution new parameters: " << std::endl << distDisc2D
    << std::endl << std::endl;
  if (distDisc2D.getMinSupport() != Eigen::Matrix<int, 2, 1>(2, 2))
    return 1;
  if (distDisc2D.getMaxSupport() != Eigen::Matrix<int, 2, 1>(5, 5))
    return 1;

  std::cout << "pdf((2, 2)): " << std::fixed
    << distDisc2D(Eigen::Matrix<int, 2, 1>(2, 2)) << std::endl << std::endl;
  if (fabs(distDisc2D(Eigen::Matrix<int, 2, 1>(2, 2)) - 1.0 / 16.0) >
      std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf((5, 5)): " << std::fixed
    << distDisc2D(Eigen::Matrix<int, 2, 1>(5, 5)) << std::endl << std::endl;
  if (fabs(distDisc2D(Eigen::Matrix<int, 2, 1>(5, 5)) -  1.0 / 16.0) >
      std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf((3, 3)): " << std::fixed
    << distDisc2D(Eigen::Matrix<int, 2, 1>(3, 3)) << std::endl << std::endl;
  if (fabs(distDisc2D(Eigen::Matrix<int, 2, 1>(3, 3)) -  1.0 / 16.0) >
      std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "pdf((10, 10)): " << std::fixed
    << distDisc2D(Eigen::Matrix<int, 2, 1>(10, 10)) << std::endl
    << std::endl;
  if (fabs(distDisc2D(Eigen::Matrix<int, 2, 1>(10, 10)) - 0.0) >
      std::numeric_limits<double>::epsilon())
    return 1;

  std::cout << "dist.getMean(): " << std::endl << std::fixed
    << distDisc2D.getMean() << std::endl << std::endl;
  std::cout << "dist.getCovariance(): " << std::endl << std::fixed
    << distDisc2D.getCovariance() << std::endl << std::endl;
  std::cout << "dist.getMode(): " << std::endl << std::fixed
    << distDisc2D.getMode() << std::endl << std::endl;
  std::cout << "dist.getMedian(): " << std::endl << std::fixed
    << distDisc2D.getMedian() << std::endl << std::endl;

  std::cout << "dist.getSample(): " << std::endl << distDisc2D.getSample()
    << std::endl << std::endl;
  std::vector<Eigen::Matrix<int, 2, 1> > samples2d;
  distDisc2D.getSamples(samples2d, 10);
  std::cout << "dist.getSamples(samples, 10): " << std::endl;
  for (size_t i = 0; i < 10; ++i)
    std::cout << std::endl << samples2d[i] << std::endl;
  std::cout << std::endl;

  UniformDistribution<int, 2> distCopy2d(distDisc2D);
  std::cout << "Copy constructor: " << std::endl << distCopy2d << std::endl
    << std::endl;
  if (distCopy2d.getMaxSupport() != distDisc2D.getMaxSupport())
    return 1;
  if (distCopy2d.getMinSupport() != distDisc2D.getMinSupport())
    return 1;
  UniformDistribution<int, 2> distAssign2d = distDisc2D;
  std::cout << "Assignment operator: " << std::endl << distAssign2d
    << std::endl;
  if (distAssign2d.getMaxSupport() != distDisc2D.getMaxSupport())
    return 1;
  if (distAssign2d.getMinSupport() != distDisc2D.getMinSupport())
    return 1;

  std::cout << std::endl;

  std::cout << "Testing uniform distribution M-D" << std::endl;
  UniformDistribution<double, Eigen::Dynamic> distMd(Eigen::Matrix<double,
    Eigen::Dynamic, 1>::Zero(5),
    Eigen::Matrix<double, Eigen::Dynamic,1>::Ones(5));
  std::cout << "Distribution parameters: " << std::endl << distMd
    << std::endl << std::endl;

  std::cout << "distMd.getSample(): " << distMd.getSample().transpose()
    << std::endl << std::endl;

  return 0;
}
