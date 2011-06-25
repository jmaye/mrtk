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

#include "visualization/Plot2D.h"
#include "statistics/Randomizer.h"
#include "statistics/NormalDistribution.h"
#include "statistics/MvNormalDistribution.h"
#include "functions/ExpFunction.h"
#include "functions/LogFunction.h"
#include "functions/FactorialFunction.h"

#include <Eigen/Core>

#include <QtGui/QApplication>

#include <vector>

#include <stdint.h>

int main(int argc, char** argv) {
  ExpFunction<> expFunction;
  std::cout << expFunction(10) << std::endl;
  LogFunction<> logFunction;
  std::cout << logFunction(10) << std::endl;
  FactorialFunction factorialFunction;
  std::cout << factorialFunction(10) << std::endl;
  QApplication app(argc, argv);
  Plot2D plot("Normal distribution");
  std::vector<double> xVector;
  std::vector<double> yVector;

#if 0
  double f64X = -10.0;
  NormalDistribution dist(0, 1);
  for (uint32_t i = 0; i < 200; i++) {
    xVector.push_back(f64X);
    yVector.push_back(dist.pdf(f64X));
    f64X += 0.1;
  }
#else
  Randomizer randomizer;
//  std::vector<double> dataVector;
//  for (uint32_t i = 0; i < 10000; i++)
//    dataVector.push_back(randomizer.sampleNormal(0, 1));

//  double f64X = -10.0;
//  for (uint32_t i = 0; i < 200; i++) {
//    xVector.push_back(f64X);
//    f64X += 0.1;
//  }

//  yVector.resize(200, 0.0);
//  for (uint32_t i = 0; i < dataVector.size(); i++) {
//    if (dataVector[i] >= -10.0 && dataVector[i] <= 10.0)
//      yVector[ceil((dataVector[i] + 10.0) / 0.1)]++;
//  }
  Eigen::Vector2d meanVector(0, 0);
  Eigen::Matrix2d covarianceMatrix;
  covarianceMatrix << 1.0, -0.5, -0.5, 1.0;
  MvNormalDistribution mvn(meanVector, covarianceMatrix);
  std::cout << mvn << std::endl;
  NormalDistribution dist(0, 10);
  std::cout << dist << std::endl;
  for (uint32_t i = 0; i < 10000; i++) {
    //Eigen::Vector2d sampleVector = randomizer.sampleNormal(meanVector,
      //covarianceMatrix);
    Eigen::Vector2d sampleVector = mvn.sample();
    xVector.push_back(sampleVector(0));
    yVector.push_back(sampleVector(1));
  }
#endif
  plot.addCurve(xVector, yVector, "Standard");
  plot.show();
  return app.exec();
}
