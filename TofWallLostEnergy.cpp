#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TLegend.h"
#include "TMath.h"
#include"TGraph.h"
#include "TMatrixD.h"
#include "TMultiGraph.h"
#include "TROOT.h"
#include "TTree.h"
#include "TRandom.h"
#include "TStyle.h"
#include "THStack.h"
 #include <numeric>
void macro(){
TFile* file= new TFile("tree4306_newgeom_FEB2021.root");
file->ls();
TTree* TOut3=(TTree*)file->Get("Tree;3");
TTree* TOut2=(TTree*)file->Get("Tree;2");
TH1F *hTWLostEnergy[8];
hTWLostEnergy[0]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[1]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[2]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[3]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[4]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[5]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[6]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[7]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
TH1F *hTWCahrge= new TH1F("TWLostEnergy","Lost Energy TW",10,0,10);
std::vector<double>  *TWDe1Point=0;
std::vector<int>     *TWChargePoint=0;
TBranch        *b_TWDe1Point=0; 
TBranch        *b_TWChargePoint=0;
  Int_t nentries=TOut3->GetEntries(); // numero di entries nel tree
  std::cout << " nentries in tree = " << nentries << std::endl;
TOut3->SetBranchAddress("TWChargePoint", &TWChargePoint, &b_TWChargePoint);
TOut3->SetBranchAddress("TWDe1Point", &TWDe1Point,&b_TWDe1Point);
  for(Int_t i=0;i<nentries;i++){
      Long64_t tentry= TOut3->LoadTree(i);
      b_TWDe1Point->GetEntry(tentry);
      b_TWChargePoint->GetEntry(tentry);
      for(UInt_t j=0;j<TWDe1Point->size();++j){
        if(TWChargePoint->at(j)==1){hTWLostEnergy[0]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==2){hTWLostEnergy[1]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==3){hTWLostEnergy[2]->Fill(TWDe1Point->at(j));} 
      else if(TWChargePoint->at(j)==4){hTWLostEnergy[3]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==5){hTWLostEnergy[4]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==6){hTWLostEnergy[5]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==7){hTWLostEnergy[6]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==8){hTWLostEnergy[7]->Fill(TWDe1Point->at(j));}
      }}
      hTWLostEnergy[0]->SetLineColor(kYellow);
      hTWLostEnergy[1]->SetLineColor(kOrange);
      hTWLostEnergy[2]->SetLineColor(kRed);
      hTWLostEnergy[3]->SetLineColor(kPink);
      hTWLostEnergy[4]->SetLineColor(kMagenta);
      hTWLostEnergy[5]->SetLineColor(kViolet);
      hTWLostEnergy[6]->SetLineColor(kBlue);
      hTWLostEnergy[7]->SetLineColor(kGreen);
       THStack *hs = new THStack("TWLostEnergy","TWLostEnergy");
       for(int i=0;i<8;++i){
         hs->Add(hTWLostEnergy[i]);
       }
TCanvas *c1= new TCanvas();
gPad->SetLogy();
hs->Draw();
}
