#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include <TFile.h>
#include <TObjString.h>

/// TO COMPILE 
/// g++ `root-config --cflags --glibs` -o EXECUTABLE AGILE_write.cpp

/// MORE INFO
/// andrea.coccaro AT cern DOT ch

int main(int argc, char **argv) {

  if (argc <= 2) {
    std::cout << "Purpose: convert a JSON file in a TObjString" << std::endl;
    std::cout << "Context: deep learning for flavour tagging in athena" << std::endl;
    std::cout << "Inputs:" << std::endl;
    std::cout << "    - input JSON file" << std::endl;
    std::cout << "    - output ROOT file" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "    - AGILE_write $INPUT_JSON_FILE $OUTPUT_ROOT_FILE" << std::endl;
    return 1;
  }

  std::string input = argv[1];
  std::cout << "input JSON file " << input << std::endl;
  std::string output = argv[2];
  std::cout << "output ROOT file " << output << std::endl;

  TFile *f = new TFile(output.c_str(), "update","",0);
  f->mkdir("DL1/AntiKt4EMTopo");
  f->cd("DL1/AntiKt4EMTopo");

  std::ifstream input_file(input);
  std::string line_string;
  std::string input_file_str;
  while (std::getline(input_file, line_string)) {
    input_file_str += line_string+ ' ' ;
  }

  TObjString comment(input_file_str.c_str());
  comment.Write("weights");
  f->Write();
  f->Close();
  delete f;

  return 0;
}
