/*************************************************************
* @author Triston Ruiseco
* @file Integral.h
* @date 03/08/2021
* @brief This class contains methods to numerically integrate a function.
*************************************************************/

#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <functional>

class Integral
{
public:

  /*
  * @pre none
  * @post none
  * @return the trapezoidal rule approximation of the integral of the
  *          the function f on [a,b] in i intervals
  */
  static double Trapz(std::function<double (double)> f, double a,
                      double b, int i);

  /*
  * @pre none
  * @post none
  * @return the four-point Gauss-Legendre approximation of the integral of
  *          the function f on [a,b] in i intervals
  */
  static double FourPointGauss(std::function<double (double)> f,
                      double a, double b, int i);

  /*
  * @pre none
  * @post none
  * @return the six-point Gauss-Legendre approximation of the integral of
  *          the function f on [a,b] in i intervals
  */
  static double SixPointGauss(std::function<double (double)> f,
                                double a, double b, int i);

  /*
  * @pre none
  * @post none
  * @return the ten-point Gauss-Legendre approximation of the integral of
  *          the function f on [a,b] in i intervals
  */
  static double TenPointGauss(std::function<double (double)> f,
                                double a, double b, int i);
};

#endif
