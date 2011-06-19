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

#include <QtGui/QApplication>

#include <vector>

#include <stdint.h>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Plot2D plot("Normal distribution");
  std::vector<double> xVector;
  std::vector<double> yVector;

#if 0
  double f64X = -10.0;
  NormalDistribution dist(0, 5);
  for (uint32_t i = 0; i < 200; i++) {
    xVector.push_back(f64X);
    yVector.push_back(dist.pdf(f64X));
    f64X += 0.1;
  }
#else
  Randomizer randomizer;
  std::vector<double> dataVector;
  for (uint32_t i = 0; i < 10000; i++)
    dataVector.push_back(randomizer.sampleNormal(0, 5));

  double f64X = -10.0;
  for (uint32_t i = 0; i < 200; i++) {
    xVector.push_back(f64X);
    f64X += 0.1;
  }

  yVector.resize(200, 0);
  for (uint32_t i = 0; i < dataVector.size(); i++) {
    if (dataVector[i] >= -10 && dataVector[i] <= 10)
      yVector[ceil((dataVector[i] + 10) / 0.1)]++;
  }
#endif
  plot.addCurve(xVector, yVector, "Standard");
  plot.show();
  return app.exec();
}
