#include <iostream>
#include <cmath>
#include <string>

#include "Integral.h"

using std::asin, std::log, std::abs, std::sqrt, std::cout, std::string,
      std::stoi;

// Program-specific helper functions
/*
* param a: first string to be compared
* param b: second string to be compared
* return 1 if a & b are identical character-wise and in length, 0 otherwise
*/
bool strsame(string a, string b){
  if(a.length()==b.length()){
    int n = a.length();
    for(int i = 0; i < n; i++){
      if(a.at(i)!=b.at(i)){
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

// Test function
double f(double x){
  return log(x*x - x);
}

// Antiderivative of test function
double F(double x){
  return x*f(x) - log(x-1) - 2*x;
}

// Begin primary program function
int main(int argc, char** argv){

  // Command line options parsing variable declarations
  bool printhelp = 0;
  bool argexists = 0;
  int mode = 0;
  int min = 1;
  int max = 10;
  int step = 1;

  // Parse and process command line options
  for(int i = 1; i < argc; ++i){
    if(strsame(argv[i],"--help")){
      argexists = 1;
      printhelp = 1;
    }
    if(strsame(argv[i],"-h")){
      argexists = 1;
      printhelp = 1;
    }
    if(strsame(argv[i],"-vals")){
      argexists = 1;
      mode = 0;
    }
    if(strsame(argv[i],"-err")){
      argexists = 1;
      mode = 1;
    }
    if(strsame(argv[i],"-min")){
      argexists = 1;
      min = stoi(argv[++i]);
      if(min < 1){
        min = 1;
      }
    }
    if(strsame(argv[i],"-max")){
      argexists = 1;
      max = stoi(argv[++i]);
      if(max < 2){
        max = 2;
      }
    }
    if(strsame(argv[i],"-step")){
      argexists = 1;
      step = stoi(argv[++i]);
      if(step < 1){
        step = 1;
      }
    }
    if(!argexists){
      printhelp = 1;
      cout << "Undefined option: " << argv[i] << "\n";
    }
  }

  /* Print the executable usage instructions if the user adds -h or --help,
     provides an undefined option, or does not provide necessary arguments */
  if(printhelp){
    cout << "Usage: " << argv[0] << " [options]\n"
         << "  options:\n"
         << "   --help(-h)          print options\n"
         << "   -vals               mode to compare the values of various"
         << "                           integration methods at increasing"
         << "                           interval counts (default)\n"
         << "   -err                mode to compare the errors of various"
         << "                           integration methods at increasing"
         << "                           interval counts\n"
         << "   -min [int]  (=1)    smallest number of intervals/integration\n"
         << "   -max [int]  (=10)   largest number of intervals/integration\n"
         << "   -step [int] (=1)    step size between number of intervals/integration\n";
    return 0;
  }

  // Integration bounds
  double xmin = 5.0;
  double xmax = 10.0;

  if(mode == 0){
    for(int i = min; i < max; i += step){
      cout << "\n\nIntegral of f(x) = ln(x^2 - x) on (5,10) in " << i << " intervals using:"
           << "\n(a) The Trapezoidal Rule: \t" << Integral::Trapz(f, xmin, xmax, i)
           << "\n(b) 04-Point Gauss-Legendre:  \t" << Integral::FourPointGauss(f, xmin, xmax, i)
           << "\n(c) 06-Gauss Gauss-Legendre:  \t" << Integral::SixPointGauss(f, xmin, xmax, i)
           << "\n(d) 10-Point Gauss-Legendre: \t" << Integral::TenPointGauss(f, xmin, xmax, i)
           << "\n(e) Analytical Solution: \t" << F(xmax)-F(xmin);
    }
  } else {
    double a, b, c;
    cout << "Legend: \n"
         << "\t(a) The Trapezoidal Rule\n"
         << "\t(b) 04-Point Gauss-Legendre\n"
         << "\t(c) Analytical Solution\n";
    for(int i = min; i < max; i += step){
      a = Integral::Trapz(f, xmin, xmax, i);
      b = Integral::FourPointGauss(f, xmin, xmax, i);
      c = F(xmax)-F(xmin);
      cout << "\n\nintegral of f(x) = ln(x^2 - x) on (5,10) in " << i << " intervals with"
           << "\n|(a) - (b)| =\t" << abs(a-b)
           << "\n|(c) - (a)| =\t" << abs(c-a)
           << "\n|(c) - (b)| =\t" << abs(c-b);
    }
  }
  cout << "\n\n";
  return 0;
}
