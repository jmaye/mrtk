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

/** \file EstimatorMLBatch.h
    \brief This file defines the EstimatorMLBatch class, which implements batch
           maximum likelihood estimators for various distributions
  */

#ifndef ESTIMATORMLBATCH_H
#define ESTIMATORMLBATCH_H

#include "statistics/EstimatorMLBatchNormal1v.h"
#include "statistics/EstimatorMLBatchNormalMv.h"
#include "statistics/EstimatorMLBatchCategorical.h"
#include "statistics/EstimatorMLBatchMultinomial.h"
#include "statistics/EstimatorMLBatchExponential.h"
#include "statistics/EstimatorMLBatchGeometric.h"
#include "statistics/EstimatorMLBatchPoisson.h"
#include "statistics/EstimatorMLBatchLinearRegression.h"
#include "statistics/EstimatorMLBatchMixtureLinearRegression.h"
#include "statistics/EstimatorMLBatchMixtureNormal1v.h"
#include "statistics/EstimatorMLBatchMixtureNormalMv.h"

#endif // ESTIMATORMLBATCH
