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

#include <Eigen/Core>

#include <QtGui/QApplication>

class MvN :
  public Function,
  public MvNormalDistribution {
  public:
    MvN(const Eigen::VectorXd& meanVector, const Eigen::MatrixXd&
      covarianceMatrix) :
      MvNormalDistribution(meanVector, covarianceMatrix) {
    }

    double operator()(double f64X, double f64Y) {
      Eigen::Vector2d inputVector(f64X, f64Y);
      return pdf(inputVector);
    }
};

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  SurfacePlot plot("Multivariate Normal Distribution");
  Eigen::Vector2d meanVector(0, 0);
  Eigen::Matrix2d covarianceMatrix;
  covarianceMatrix << 1.0, -0.5, -0.5, 1.0;
  MvN mvn(meanVector, covarianceMatrix);
  plot.addFunction(mvn);
  plot.resize(800, 600);
  plot.show();
  return a.exec();
}
