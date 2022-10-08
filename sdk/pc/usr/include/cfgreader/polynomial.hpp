/**
 * Copyright (C) 2019 Parrot Drones SAS
 */

#ifndef CFGREADER_POLYNOMIAL_HPP
#define CFGREADER_POLYNOMIAL_HPP
#include <initializer_list>
#include "Eigen/Eigen"

namespace cfgreader {
template<typename T> class Polynomial
{
    using Coefficients = Eigen::Matrix<T, Eigen::Dynamic, 1>;

private:
    /* For n-order Polynomial, coefficients are set as
     * [a_n, a_(n-1), ... a_1, a_0] */
    Coefficients coefficients;

public:

    void init(int param_size, const T * param_coefs)
    {
        coefficients.resize(param_size);
        for(int i = 0; i < param_size; i++)
            coefficients(i) = param_coefs[i];
    }

    void init(const std::initializer_list<T> param_coef)
    {
        coefficients.resize(param_coef.size());
        int n = 0;
        const T * it;
        for (it = param_coef.begin(); it != param_coef.end(); ++it)
            coefficients(n++) = *it;
    }

    void init(const Coefficients& param_coefs)
    {
        coefficients = param_coefs;
    }

    T compute(T x) const
    {
        T res = {};
        for (int i = 0; i < coefficients.size(); ++i)
            res = (res * x) + coefficients(i);
        return res;
    }

    T evaluateDerivate(T x)
    {
        T res = {};
        if (coefficients.size() > 1)
            for (int i = 0; i < coefficients.size()-1; ++i)
                res = (res * x)
                    + (coefficients.size() - 1 - i) * coefficients(i);
        return res;
    }

    T evaluateSecondDerivate(T x)
    {
        T res = {};
        if (coefficients.size() > 2)
            for (int i = 0; i < coefficients.size()-2; ++i)
                res = (res * x)
                    + (  (coefficients.size() - 1 - i)
                       * (coefficients.size() - 2 - i)
                       * coefficients(i));
        return res;
    }
};
}

#endif
