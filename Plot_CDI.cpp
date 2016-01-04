#include <iostream>
#include <string>

#include <TFile.h>
#include <TString.h>
#include <TKey.h>
#include <TROOT.h>
#include <TClass.h>
#include <TCanvas.h>

/// TO COMPILE
/// g++ `root-config --cflags --glibs` -o EXECUTABLE Plot_CDI.cpp

void calldir(TDirectory *dir) {

  TKey *key;
  TIter next(dir->GetListOfKeys());

  while ((key = (TKey*)next())) {
    if (key->IsFolder()) { 
      dir->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      calldir(subdir);
      continue;
    }
    TString output = dir->GetPath();
    output.ReplaceAll("/","-");
    output.ReplaceAll(" ","");
    int i = output.Index("root");
    output.Replace(0,i+6,"");

    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TCanvas")) continue;
    TCanvas *c = (TCanvas*)key->ReadObj();
    c->Print(output+".pdf");
  }
}

int main(int argc, char **argv) {

  if (argc <= 1) {
    std::cout << "Purpose: plot CDI-related histograms (tested on the Tagger-Trends file)" << std::endl;
    std::cout << "Context: flavour tagging calibration" << std::endl;
    std::cout << "Inputs:" << std::endl;
    std::cout << "    - input ROOT file" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "    - Plot_CDI $INPUT_ROOT_FILE" << std::endl;
    return 1;
  }

  std::string input = argv[1];
  std::cout << "input ROOT file " << input << std::endl;

  TFile *f = TFile::Open(input.c_str());
  calldir(f);
  delete f;
  return 0;
}
