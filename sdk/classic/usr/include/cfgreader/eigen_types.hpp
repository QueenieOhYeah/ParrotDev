/**
 * Copyright (C) 2019 Parrot Drones SAS
 */

#ifndef CFGREADER_EIGEN_TYPES_HPP
#define CFGREADER_EIGEN_TYPES_HPP

#include <Eigen/Eigen>
#include "polynomial.hpp"

namespace cfgreader
{

typedef Eigen::Matrix<float,5,1> Vector5f;
typedef Eigen::Matrix<float,6,1> Vector6f;
typedef Eigen::Matrix<float,5,5> Matrix5f;
typedef Eigen::Matrix<float,6,6> Matrix6f;
typedef Eigen::Matrix<float,18,18> Matrix18f;
typedef Eigen::Array<bool, Eigen::Dynamic,1> ArrayXb;
typedef Eigen::Array<bool,2,1> Array2b;
typedef Eigen::Array<bool,3,1> Array3b;

typedef cfgreader::Polynomial<float> PolynomialVoltageCompensation;
typedef Eigen::Matrix<PolynomialVoltageCompensation, Eigen::Dynamic, 1> VectorPolynomialVoltageCompensation;

}

#endif
