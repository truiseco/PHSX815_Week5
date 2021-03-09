/*************************************************************
* @author Triston Ruiseco
* @file Integral.cpp
* @date 03/08/2021
* @brief Implementation file for the Integral class.
*************************************************************/

#include <iostream>
#include "Integral.h"

double Integral::Trapz(std::function<double (double)> f, double a, double b, int i){
  double s = 0.0;
  double x = a;
  double h = (b-a)/(i);
  for(int k = 0; k < i; k++){
    s += f(x) + f(x+h);
    x += h;
  }
  return 0.5*h*s;
}

double Integral::FourPointGauss(std::function<double (double)> f, double a, double b, int i){
  const double x[]={0.33998104358486, 0.86113631159405};
  const double w[]={0.65214515486255, 0.34785484513745};
  double xm, xr, dx, s = 0.0;
  double h = (b-a)/i;
  double xlo = a;
  double xhi = a + h;
  for(int j = 0; j < i; j++){
    xm = 0.5*(xhi+xlo);
    xr = 0.5*(xhi-xlo);
    for(int k = 0; k < 2; k++){
      dx = xr*x[k];
      s += xr*w[k]*(f(xm+dx) + f(xm-dx));
    }
    xlo = xhi;
    xhi += h;
  }
  return s;
}

double Integral::SixPointGauss(std::function<double (double)> f, double a, double b, int i){
  const double x[]={0.2386191860832, 0.6612093864663, 0.93246951420315};
  const double w[]={0.46791393457269, 0.36076157304814, 0.17132449237917};
  double xm, xr, dx, s = 0.0;
  double h = (b-a)/i;
  double xlo = a;
  double xhi = a + h;
  for(int j = 0; j < i; j++){
    xm = 0.5*(xhi+xlo);
    xr = 0.5*(xhi-xlo);
    for(int k = 0; k < 3; k++){
      dx = xr*x[k];
      s += xr*w[k]*(f(xm+dx) + f(xm-dx));
    }
    xlo = xhi;
    xhi += h;
  }
  return s;
}

double Integral::TenPointGauss(std::function<double (double)> f, double a, double b, int i){
  static const double x[]={0.1488743389816312,0.4333953941292472,
    0.6794095682990244,0.8650633666889845,0.9739065285171717};
  static const double w[]={0.2955242247147529,0.2692667193099963,
    0.2190863625159821,0.1494513491505806,0.0666713443086881};
  double xm, xr, dx, s = 0.0;
  double h = (b-a)/i;
  double xlo = a;
  double xhi = a + h;
  for(int j = 0; j < i; j++){
    xm = 0.5*(xhi+xlo);
    xr = 0.5*(xhi-xlo);
    for (int k=0;k<5;k++) {
      dx = xr*x[k];
      s += xr*w[k]*(f(xm+dx) + f(xm-dx));
    }
    xlo = xhi;
    xhi += h;
  }
  return s;
}
