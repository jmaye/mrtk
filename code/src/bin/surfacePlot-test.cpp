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

#include "statistics/MvNormalDistribution.h"
#include "visualization/SurfacePlot.h"
#include "visualization/Function.h"

#include <QtGui/QApplication>

#include <iostream>
#include <vector>

class MvN :
  public Function,
  public MvNormalDistribution {
  public:
    MvN(const std::vector<double>& meanVector,
      const std::vector<std::vector<double> >& covarianceMatrix) :
      MvNormalDistribution(meanVector, covarianceMatrix) {
    }

    double operator()(double f64X, double f64Y) {
      std::vector<double> inputVector(2);
      inputVector[0] = f64X;
      inputVector[1] = f64Y;
      return pdf(inputVector);
    }
};

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  SurfacePlot plot("Multivariate Normal Distribution");
  std::vector<double> meanVector(2);
  std::vector<std::vector<double> > covarianceMatrix(2);
  meanVector[0] = 0;
  meanVector[1] = 0;
  covarianceMatrix[0].resize(2);
  covarianceMatrix[0][0] = 1.0;
  covarianceMatrix[0][1] = -0.5;
  covarianceMatrix[1].resize(2);
  covarianceMatrix[1][0] = -0.5;
  covarianceMatrix[1][1] = 1.0;
  MvN mvn(meanVector, covarianceMatrix);
  plot.addFunction(mvn);
  plot.resize(800, 600);
  plot.show();
  return a.exec();
}
