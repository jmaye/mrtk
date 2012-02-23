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

/** \file Randomizer.cpp
    \brief This file is a testing binary for the Randomizer class
  */

#include <iostream>

#include "statistics/Randomizer.h"

int main(int argc, char** argv) {
  std::cout << "Sampling discrete uniform distribution" << std::endl;
  Randomizer<size_t> rndDiscUnif;
  std::cout << "Seed: " << rndDiscUnif.getSeed() << std::endl;
  std::cout << "Stream: " << std::endl << rndDiscUnif << std::endl;
  std::cout << rndDiscUnif.sampleUniform() << std::endl;
  try {
    rndDiscUnif.sampleUniform(2, 1);
  }
  catch (BadArgumentException<size_t>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "Sampling continuous uniform distribution" << std::endl;
  Randomizer<double> rndContUnif;
  std::cout << "Seed: " << rndContUnif.getSeed() << std::endl;
  std::cout << "Stream: " << std::endl << rndContUnif << std::endl;
  std::cout << rndContUnif.sampleUniform() << std::endl;
  try {
    rndContUnif.sampleUniform(2, 1);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "Sampling normal distribution" << std::endl;
  Randomizer<double> rndNormal;
  std::cout << "Seed: " << rndNormal.getSeed() << std::endl;
  std::cout << "Stream: " << std::endl << rndNormal << std::endl;
  std::cout << rndNormal.sampleNormal() << std::endl;
  try {
    rndContUnif.sampleNormal(0, 0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "Sampling categorical distribution" << std::endl;
  Randomizer<double, 2> rndCategorical;
  std::cout << "Seed: " << rndCategorical.getSeed() << std::endl;
  std::cout << "Stream: " << std::endl << rndCategorical << std::endl;
  std::cout << rndCategorical.sampleCategorical(
    Eigen::Matrix<double, 2, 1>(0.1, 0.9)) << std::endl << std::endl;
  try {
    rndCategorical.sampleCategorical(Eigen::Matrix<double, 2, 1>(0.1, 1.2));
  }
  catch (BadArgumentException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "Sampling Poisson distribution" << std::endl;
  Randomizer<double> rndPoisson;
  std::cout << "Seed: " << rndPoisson.getSeed() << std::endl;
  std::cout << "Stream: " << std::endl << rndPoisson << std::endl;
  std::cout << rndPoisson.samplePoisson(1.0) << std::endl;
  try {
    rndPoisson.samplePoisson(-1.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "Sampling exponential distribution" << std::endl;
  Randomizer<double> rndExp;
  std::cout << "Seed: " << rndExp.getSeed() << std::endl;
  std::cout << "Stream: " << std::endl << rndExp << std::endl;
  std::cout << rndExp.sampleExponential(1.0) << std::endl;
  try {
    rndPoisson.sampleExponential(-1.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "Sampling geometric distribution" << std::endl;
  Randomizer<double> rndGeom;
  std::cout << "Seed: " << rndGeom.getSeed() << std::endl;
  std::cout << "Stream: " << std::endl << rndGeom << std::endl;
  std::cout << rndGeom.sampleGeometric(0.5) << std::endl;
  try {
    rndGeom.sampleGeometric(-1.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "Sampling gamma distribution" << std::endl;
  Randomizer<double> rndGamma;
  std::cout << "Seed: " << rndGamma.getSeed() << std::endl;
  std::cout << "Stream: " << std::endl << rndGamma << std::endl;
  std::cout << rndGamma.sampleGamma(0.5, 0.5) << std::endl;
  try {
    rndGeom.sampleGamma(-1.0, -1.0);
  }
  catch (BadArgumentException<double>& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
