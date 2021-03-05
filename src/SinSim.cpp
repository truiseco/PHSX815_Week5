// Standard Library Includes

// ROOT Includes
#include "TGraph.h"
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLine.h"
#include "TMath.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TRandom.h"

// Local Includes
#include "Random.h"

// Directives and declarations for namespaces and namespace members
using std::acos, std::string, std::cout, std::stoi, std::sqrt;

// Global definitions
const double PI = acos(-1);
Random rng;
double bin_width;

// Program-specific helper function declarations
/*
* param a: first string to be compared
* param b: second string to be compared
* return 1 if a & b are identical character-wise and in length, 0 otherwise
*/
bool strsame(string a, string b);

/*
* return uniformly distributed random value between min and max
*/
double range(double min, double max);

// Several proposal functions
double Flat(double x);        // f(x) = 1
double SemiCircle(double x);  // semicirlce of radius pi/2 centered at x = pi/2
double SemiEllipse(double x); /* semiellipse with semi-minor axis 1
                                semi-major axis pi/2 centered at x = pi/2 */
// Plotting helper functions
double PlotFlat(double* x, double* par);
double PlotSemiCircle(double* x, double* par);
double PlotSemiEllipse(double* x, double* par);
double PlotSin(double* x, double* par);

/*
* Visualizes and saves results to RandomSin.png
*/
void PlotResults(TH1D* hist, int mode, int Nsample);

// Begin primary program function
int main(int argc, char** argv){

  // Command line options parsing variable declarations
  bool argexists = 0;
  bool printhelp = 0;
  int mode = 0;
  int Nsample = 0;

  // Parse and process command line options
  for(int i = 1; i < argc; ++i){
    argexists = 0;
    if(strsame(argv[i],"--help") || strsame(argv[i],"-h")){
      argexists = 1;
      printhelp = 1;
    }
    if(strsame(argv[i],"--flat")){
      argexists = 1;
      mode = 0;
    }
    if(strsame(argv[i],"--circle")){
      argexists = 1;
      mode = 1;
    }
    if(strsame(argv[i],"--ellipse")){
      argexists = 1;
      mode = 2;
    }
    if(strsame(argv[i],"-Nsample")){
      argexists = 1;
      Nsample = stoi(argv[++i]);
      if(Nsample <= 0){
        printhelp = 1;
        cout << "-Nsample must be a positive integer\n";
      }
    }
    if(strsame(argv[i], ""))
    if(!argexists){
      printhelp = 1;
      cout << "Undefined option: " << argv[i] << "\n";
    }
  }

  /* Print the executable usage instructions if the user adds -h or --help,
     doesn't provide input, or provides an undefined option */
  if(printhelp){
    cout << "Usage: " << argv[0] << " [options] -Nsample [integer]\n"
         << "  required:\n"
         << "   -Nsample [integer]  number of random samples\n"
         << "  optional:\n"
         << "   --help(-h)          print options\n"
         << "   --flat              use flat proposal function (default)\n"
         << "   --circle            use semicircular proposal function\n"
         << "   --ellipse           use semi-elliptical proposal function\n";

    return 0;
  }

  // Simulation/sampling/visualization helper variables
  double X = 0.0;
  double R = 0.0;
  double ran = 0.0;
  int Nsuccess = 0;
  int Ntrial = 0;


  // Simulation storage and visualization objects
  TH1D* hist = new TH1D("hist", "hist", 100, 0, PI);

  // Simulate distribution via rejection sampling
  while(Nsuccess < Nsample){
    ++Ntrial;
    X = range(0, PI);
    R = sin(X);
    if(mode == 1){
      R /= SemiCircle(X);
    }
    if(mode == 2){
      R /= SemiEllipse(X);
    }
    ran = rng.rand();
    if(ran <= R){ // Accept and iterate
      hist->Fill(X);
      ++Nsuccess;
    } // Else reject and repeat
  }

  // Plot what we've got
  PlotResults(hist, mode, Nsample);

  // Print efficiency (avoid division by zero)
  if(Ntrial > 0){
    cout << "Efficiency for sin(x): " << double(Nsample)/Ntrial << "\n";
  }
  return 0;
}


// Program-specific helper function definitions
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

double range(double min, double max){
  return min + (max-min)*rng.rand();
}

double Flat(double x){
  return 1;
}
double SemiCircle(double x){
  return sqrt(-x*(x-PI));
}
double SemiEllipse(double x){
  return (2/PI)*SemiCircle(x);
}

double PlotFlat(double* x, double* par){
  return bin_width*Flat(x[0]);
}
double PlotSemiCircle(double* x, double* par){
  return bin_width*SemiCircle(x[0]);
}
double PlotSemiEllipse(double* x, double* par){
  return bin_width*SemiEllipse(x[0]);
}
double PlotSin(double* x, double* par){
  return bin_width*sin(x[0]);
}

void PlotResults(TH1D* hist, int mode, int Nsample){
  TCanvas* canvas = new TCanvas("canvas", "canvas", 450, 400);

  // Record and set canvas margins
  double ml = 0.15;
  double mr = 0.08;
  double mb = 0.15;
  double mt = 0.07;
  canvas->SetLeftMargin(ml);
  canvas->SetRightMargin(mr);
  canvas->SetBottomMargin(mb);
  canvas->SetTopMargin(mt);

  // Visualization customizations
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  canvas->SetGridx();
  canvas->SetGridy();

  // Draw and set current pad to this canvas
  canvas->Draw();
  canvas->cd();

  // Visualization customizations
  if(hist->Integral() > 0)
    hist->Scale(1.0/hist->Integral());
  hist->SetLineColor(kAzure+3);
  hist->SetFillColor(kBlue);
  hist->SetFillStyle(3003);
  hist->GetXaxis()->CenterTitle();
  hist->GetXaxis()->SetTitleFont(42);
  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->SetLabelFont(42);
  hist->GetXaxis()->SetLabelSize(0.04);
  hist->GetXaxis()->SetTitle("Domain");
  hist->GetXaxis()->SetTickSize(0.0);
  hist->GetYaxis()->CenterTitle();
  hist->GetYaxis()->SetTitleFont(42);
  hist->GetYaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetTitleOffset(1.2);
  hist->GetYaxis()->SetLabelFont(42);
  hist->GetYaxis()->SetLabelSize(0.035);
  hist->GetYaxis()->SetTitle("Probability / bin");
  hist->GetYaxis()->SetRangeUser(std::min(0.0, 1./double(Nsample+1)),
				   80*std::max(hist->GetMaximum(), 0.0));
  hist->Draw("hist");

  // Plot target
  TF1* target = new TF1("myflat", PlotSin, 0.0, PI);
  target->SetLineColor(kAzure+2);
  target->SetLineWidth(2);
  target->Draw("same");

  // Plot proposal
  TF1* proposal;
  if(mode == 0){
    proposal = new TF1("proposal", PlotFlat, 0.0, PI);
  } else if(mode == 1){
    proposal = new TF1("proposal", PlotSemiCircle, 0.0, PI);
  } else {
    proposal = new TF1("proposal", PlotSemiEllipse, 0.0, PI);
  }
  proposal->SetLineColor(kRed+2);
  proposal->SetLineWidth(2);
  proposal->Draw("same");

  // Draw legend
  TLegend* leg = new TLegend(0.17,0.72,0.3946,0.925);
  leg->SetTextFont(132);
  leg->SetTextSize(0.045);
  leg->SetFillColor(kWhite);
  leg->SetLineColor(kWhite);
  leg->SetShadowColor(kWhite);
  leg->AddEntry(target, "target" , "l");
  leg->AddEntry(proposal, "proposal", "l");
  leg->AddEntry(hist, "samples");
  leg->Draw();

  // Paint and save canvas
  canvas->SaveAs("RandomSin.png");
}
