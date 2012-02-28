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

/** \file Grid.cpp
    \brief This file is a testing binary for the Grid class.
  */

#include <iostream>

#include "data-structures/Grid.h"

int main (int argc, char** argv) {
  std::cout << "Testing Grid2d real" << std::endl;
  Grid<double, size_t, 2> grid2d(Eigen::Matrix<double, 2, 1>(0.0, 0.0),
    Eigen::Matrix<double, 2, 1>(4.0, 4.0),
    Eigen::Matrix<double, 2, 1>(0.5, 0.5));
  std::cout << "Grid parameters: " << std::endl << grid2d << std::endl;
  std::cout << "Testing accessors:" << std::endl;
  std::cout << "Cells number: " << grid2d.getNumCells().transpose()
    << std::endl;
  std::cout << "Cells number total: " << grid2d.getNumCellsTot() << std::endl;
  std::cout << "Grid max: " << grid2d.getMaximum().transpose() << std::endl;
  std::cout << "Grid min: " << grid2d.getMinimum().transpose() << std::endl;
  std::cout << "Grid res: " << grid2d.getResolution().transpose() << std::endl;
  std::cout << "Incrementing each element" << std::endl;
  for (size_t i = 0; i < grid2d.getNumCells()(0); ++i)
    for (size_t j = 0; j < grid2d.getNumCells()(1); ++j)
      grid2d[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()]++;
  std::cout << "point(0.0, 0.0) is at index: " <<
    grid2d.getIndex(Eigen::Matrix<double, 2, 1>(0.0, 0.0)).transpose()
    << std::endl;
  std::cout << "point(0.5, 0.5) is at index: " <<
    grid2d.getIndex(Eigen::Matrix<double, 2, 1>(0.5, 0.5)).transpose()
    << std::endl;
  std::cout << "point(1.0, 1.0) is at index: " <<
    grid2d.getIndex(Eigen::Matrix<double, 2, 1>(1.0, 1.0)).transpose()
    << std::endl;
  std::cout << "point(2.0, 2.0) is at index: " <<
    grid2d.getIndex(Eigen::Matrix<double, 2, 1>(2.0, 2.0)).transpose()
    << std::endl;
  std::cout << "point(3.0, 3.0) is at index: " <<
    grid2d.getIndex(Eigen::Matrix<double, 2, 1>(3.0, 3.0)).transpose()
    << std::endl;
  std::cout << "point(3.9, 3.9) is at index: " <<
    grid2d.getIndex(Eigen::Matrix<double, 2, 1>(3.9, 3.9)).transpose()
    << std::endl;
  std::cout << "point(4.0, 4.0) is at index: " <<
    grid2d.getIndex(Eigen::Matrix<double, 2, 1>(4.0, 4.0)).transpose()
    << std::endl;
  std::cout << "resetting the grid" << std::endl;
  grid2d.reset();

  try {
    grid2d(Eigen::Matrix<double, 2, 1>(4.1, 4.1));
  }
  catch (OutOfBoundException<Eigen::Matrix<double, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    grid2d[(Eigen::Matrix<size_t, 2, 1>() << 8, 8).finished()];
  }
  catch (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << std::endl;

  std::cout << "Testing Grid1d real" << std::endl;
  Eigen::Matrix<double, 1, 1>
    min((Eigen::Matrix<double, 1, 1>() << 0).finished());
  Eigen::Matrix<double, 1, 1>
    max((Eigen::Matrix<double, 1, 1>() << 5).finished());
  Eigen::Matrix<double, 1, 1>
    res((Eigen::Matrix<double, 1, 1>() << 0.1).finished());
  Grid<double, size_t, 1> grid1d(min, max, res);
  std::cout << "Grid parameters: " << std::endl << grid1d << std::endl;
  std::cout << "Testing accessors:" << std::endl;
  std::cout << "Cells number: " << grid1d.getNumCells().transpose()
    << std::endl;
  std::cout << "Cells number total: " << grid1d.getNumCellsTot() << std::endl;
  std::cout << "Grid max: " << grid1d.getMaximum().transpose() << std::endl;
  std::cout << "Grid min: " << grid1d.getMinimum().transpose() << std::endl;
  std::cout << "Grid res: " << grid1d.getResolution().transpose() << std::endl;
  std::cout << "Incrementing each element" << std::endl;
  for (size_t i = 0; i < grid1d.getNumCells()(0); ++i)
    grid1d[(Eigen::Matrix<size_t, 1, 1>() << i).finished()]++;

  std::cout << std::endl;

  std::cout << "Testing Grid1d int" << std::endl;
  Eigen::Matrix<int, 1, 1>
    minInt((Eigen::Matrix<int, 1, 1>() << 0).finished());
  Eigen::Matrix<int, 1, 1>
    maxInt((Eigen::Matrix<int, 1, 1>() << 5).finished());
  Eigen::Matrix<int, 1, 1>
    resInt((Eigen::Matrix<int, 1, 1>() << 1).finished());
  Grid<int, size_t, 1> grid1dInt(minInt, maxInt, resInt);
  std::cout << "Grid parameters: " << std::endl << grid1dInt << std::endl;
  std::cout << "Testing accessors:" << std::endl;
  std::cout << "Cells number: " << grid1dInt.getNumCells().transpose()
    << std::endl;
  std::cout << "Cells number total: " << grid1dInt.getNumCellsTot()
    << std::endl;
  std::cout << "Grid max: " << grid1dInt.getMaximum().transpose() << std::endl;
  std::cout << "Grid min: " << grid1dInt.getMinimum().transpose() << std::endl;
  std::cout << "Grid res: " << grid1dInt.getResolution().transpose()
    << std::endl;
  std::cout << "Incrementing each element" << std::endl;
  for (size_t i = 0; i < grid1dInt.getNumCells()(0); ++i)
    grid1dInt[(Eigen::Matrix<size_t, 1, 1>() << i).finished()]++;
  std::cout << "Grid after modif: " << std::endl << grid1dInt << std::endl;
  std::cout << "resetting the grid" << std::endl;
  grid1dInt.reset();
  std::cout << "Grid after reset: " << std::endl << grid1dInt << std::endl;
  std::cout << "Adding point 0 in the grid" << std::endl;
  grid1dInt((Eigen::Matrix<int, 1, 1>() << 0).finished())++;
  std::cout << "Adding point 1 in the grid" << std::endl;
  grid1dInt((Eigen::Matrix<int, 1, 1>() << 1).finished())++;
  std::cout << "Adding point 2 in the grid" << std::endl;
  grid1dInt((Eigen::Matrix<int, 1, 1>() << 2).finished())++;
  std::cout << "Adding point 3 in the grid" << std::endl;
  grid1dInt((Eigen::Matrix<int, 1, 1>() << 3).finished())++;
  std::cout << "Adding point 4 in the grid" << std::endl;
  grid1dInt((Eigen::Matrix<int, 1, 1>() << 4).finished())++;
  std::cout << "Adding point 5 in the grid" << std::endl;
  grid1dInt((Eigen::Matrix<int, 1, 1>() << 5).finished())++;
  std::cout << "Grid after modif: " << std::endl << grid1dInt << std::endl;
  std::cout << "Get bin center 0: " <<
    grid1dInt.getCoordinates((Eigen::Matrix<size_t, 1, 1>() << 0).finished())
    << std::endl;
  std::cout << "Get bin center 1: " <<
    grid1dInt.getCoordinates((Eigen::Matrix<size_t, 1, 1>() << 1).finished())
    << std::endl;

  return 0;
}
