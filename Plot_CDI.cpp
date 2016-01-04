#include <iostream>

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

int main() {

  TFile *f = TFile::Open("2016-Winter-13TeV-plots-MC15-CDI-Tagger-Trends.root");
  calldir(f);
  delete f;
  return 0;
}
