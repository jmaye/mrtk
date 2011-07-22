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

#include "statistics/Histogram.h"

int main(int argc, char** argv) {
  std::cout << "Testing discrete histograms" << std::endl;
  Histogram<size_t, 1> hist1DiscDefault;
  std::cout << "Histogram default parameters: " << std::endl << hist1DiscDefault
    << std::endl << std::endl;
  std::cout << "hist.getMinValue(): " << std::endl << hist1DiscDefault.
    getMinValue() << std::endl << std::endl;
  std::cout << "hist.getMaxValue(): " << std::endl << hist1DiscDefault.
    getMaxValue() << std::endl << std::endl;
  std::cout << "hist.getBinWidth(): " << std::endl << hist1DiscDefault.
    getBinWidth() << std::endl << std::endl;
  std::cout << "hist.getNumBins(): " << std::endl << hist1DiscDefault.
    getNumBins() << std::endl << std::endl;
  std::cout << "hist.addBinContent(0)" << std::endl;
  std::cout << "hist.addBinContent(1)" << std::endl;
  hist1DiscDefault.addBinContent(0);
  hist1DiscDefault.addBinContent(1);
  std::cout << "hist.getBinContent(0): " << std::endl << hist1DiscDefault.
    getBinContent(0) << std::endl << std::endl;
  if (fabs(hist1DiscDefault.getBinContent(0) - 1.0) > 1e-6)
    return 1;
  std::cout << "hist.getBinContent(1): " << std::endl << hist1DiscDefault.
    getBinContent(1) << std::endl << std::endl;
  if (fabs(hist1DiscDefault.getBinContent(1) - 1.0) > 1e-6)
    return 1;
  std::cout << "hist.setBinContent(1, 10)" << std::endl;
  hist1DiscDefault.setBinContent(1, 10);
  std::cout << "hist.getBinContent(1): " << std::endl << hist1DiscDefault.
    getBinContent(1) << std::endl << std::endl;
  if (fabs(hist1DiscDefault.getBinContent(1) - 10.0) > 1e-6)
    return 1;
  std::cout << "hist.addSample(1)" << std::endl;
  hist1DiscDefault.addSample(1);
  std::cout << "hist.addSample(2)" << std::endl;
  hist1DiscDefault.addSample(2);
  std::cout << "hist.getBinContent(1): " << std::endl << hist1DiscDefault.
    getBinContent(1) << std::endl << std::endl;
  if (fabs(hist1DiscDefault.getBinContent(1) - 11.0) > 1e-6)
    return 1;
  std::cout << "hist.getNormFactor(): " << std::endl << hist1DiscDefault.
    getNormFactor() << std::endl << std::endl;
  std::cout << "hist.getBinsSum(): " << std::endl << hist1DiscDefault.
    getBinsSum() << std::endl << std::endl;
  std::cout << "hist.getMaximumBinCount(): " << std::endl << hist1DiscDefault.
    getMaximumBinCount() << std::endl << std::endl;
  std::cout << "hist.getMaximumBin(): " << std::endl << hist1DiscDefault.
    getMaximumBin() << std::endl << std::endl;
  std::cout << "hist.getMinimumBinCount(): " << std::endl << hist1DiscDefault.
    getMinimumBinCount() << std::endl << std::endl;
  std::cout << "hist.getMinimumBin(): " << std::endl << hist1DiscDefault.
    getMinimumBin() << std::endl << std::endl;
  std::cout << "hist.getSample(): " << std::endl << hist1DiscDefault.
    getSample() << std::endl << std::endl;
  std::cout << "hist.getMeanCount(): " << std::endl << hist1DiscDefault.
    getMeanCount() << std::endl << std::endl;
  std::cout << "hist.getMeanValue(): " << std::endl << hist1DiscDefault.
    getMeanValue() << std::endl << std::endl;
  std::cout << "hist.normalize()" << std::endl;
  hist1DiscDefault.normalize();
  std::cout << "hist.getBinContent(0): " << std::endl << hist1DiscDefault.
    getBinContent(0) << std::endl << std::endl;
  if (fabs(hist1DiscDefault.getBinContent(0) - 1.0 / 12) > 1e-6)
    return 1;
  std::cout << "hist.getBinContent(1): " << std::endl << hist1DiscDefault.
    getBinContent(1) << std::endl << std::endl;
  if (fabs(hist1DiscDefault.getBinContent(1) - 11.0 / 12) > 1e-6)
    return 1;
  try {
    hist1DiscDefault.setBinContent(2, 10);
  }
  catch (OutOfBoundException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    hist1DiscDefault.getBinContent(2);
  }
  catch (OutOfBoundException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    hist1DiscDefault.addBinContent(2);
  }
  catch (OutOfBoundException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    Histogram<size_t, 1> hist1discWrong1(10, 0, 2);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    Histogram<size_t, 1> hist1discWrong2(0, 5, 10);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  Histogram<double, 1> hist1ContDefault;
  std::cout << "Testing continuous histograms" << std::endl;
  std::cout << "Histogram default parameters: " << std::endl << hist1ContDefault
    << std::endl << std::endl;
  std::cout << "hist.getMinValue(): " << std::endl << hist1ContDefault.
    getMinValue() << std::endl << std::endl;
  std::cout << "hist.getMaxValue(): " << std::endl << hist1ContDefault.
    getMaxValue() << std::endl << std::endl;
  std::cout << "hist.getBinWidth(): " << std::endl << hist1ContDefault.
    getBinWidth() << std::endl << std::endl;
  std::cout << "hist.getNumBins(): " << std::endl << hist1ContDefault.
    getNumBins() << std::endl << std::endl;
  std::cout << "hist.addBinContent(0)" << std::endl;
  hist1ContDefault.addBinContent(0);
  std::cout << "hist.getBinContent(0): " << std::endl << hist1ContDefault.
    getBinContent(0) << std::endl << std::endl;
  if (fabs(hist1ContDefault.getBinContent(0) - 1.0) > 1e-6)
    return 1;
  std::cout << "hist.setBinContent(0, 10)" << std::endl;
  hist1ContDefault.setBinContent(0, 10);
  std::cout << "hist.getBinContent(0): " << std::endl << hist1ContDefault.
    getBinContent(0) << std::endl << std::endl;
  if (fabs(hist1ContDefault.getBinContent(0) - 10.0) > 1e-6)
    return 1;
  std::cout << "hist.addSample(0.5)" << std::endl;
  hist1ContDefault.addSample(0.5);
  std::cout << "hist.addSample(1.5)" << std::endl;
  hist1ContDefault.addSample(1.5);
  std::cout << "hist.getBinContent(0): " << std::endl << hist1ContDefault.
    getBinContent(0) << std::endl << std::endl;
  if (fabs(hist1ContDefault.getBinContent(0) - 11.0) > 1e-6)
    return 1;
  try {
    hist1ContDefault.setBinContent(2, 10);
  }
  catch (OutOfBoundException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    hist1ContDefault.getBinContent(2);
  }
  catch (OutOfBoundException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    hist1ContDefault.addBinContent(2);
  }
  catch (OutOfBoundException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    Histogram<double, 1> hist1ContWrong1(10, 0, 2);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    Histogram<double, 1> hist1ContWrong2(0, 5, 10);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
