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
 
 void macro(){
     TFile* fileGeom= new TFile("tree4306_newgeom_MAR2022.root");
     TFile* filePileUp= new TFile("tree4306_pileup_MAR2022.root");
     fileGeom->ls();
     filePileUp->ls();
     TTree* TGeomOut=(TTree*)fileGeom->Get("Tree;5");
     TTree* TPileUpOut=(TTree*)filePileUp->Get("Tree;3");
     TH1F *hSCTimeNoPileUp= new TH1F("SCTimeNoPileUp","Start counter time without pile up",100,0,200);
     TH1F *hSCTimePileUp= new TH1F("SCTimePileUp","Start counter time with pile up",100,0,200);
     TH1F *hSCChargePileUp=new TH1F("SCCharge"," Carica rilasciata nel start counter",100,0,30);
     TH1F *hSCChargeNoPileUp=new TH1F("SCCharge"," Carica rilasciata nel start counter",100,0,30);
     Double_t SCCharge=0;//lo leggo da new Geom
     Double_t SCTime=0;//lo leggo da new Geom
     Bool_t SCPileup=false;//lo leggo d PileUpFile
    TBranch        *b_SCCharge=0;   
    TBranch        *b_SCTime=0;   
    TBranch        *b_SCPileup=0;
    Int_t nentriesGeom=TGeomOut->GetEntries();
    Int_t nentriesPileUp=TPileUpOut->GetEntries();
    if(nentriesGeom!=nentriesPileUp){for(int i=0;;){}}
    TGeomOut->SetBranchAddress("SCCharge", &SCCharge, &b_SCCharge);
    TGeomOut->SetBranchAddress("SCTime", &SCTime, &b_SCTime);
    TPileUpOut->SetBranchAddress("SCPileup",&SCPileup,&b_SCPileup);
   Long64_t tGeomEntry=0;
    Long64_t tPileUpEntry=0;
    for(Int_t i=0;i<nentriesGeom;++i){
        tGeomEntry=TGeomOut->LoadTree(i);
        tPileUpEntry=TPileUpOut->LoadTree(i);
        b_SCCharge->GetEntry(tGeomEntry);
        b_SCTime->GetEntry(tGeomEntry);
        b_SCPileup->GetEntry(tPileUpEntry);
        if(SCPileup==false){
            hSCTimeNoPileUp->Fill(SCTime);
            hSCChargeNoPileUp->Fill(SCCharge);
        } 
        hSCTimePileUp->Fill(SCTime);    
        hSCChargePileUp->Fill(SCCharge); 
    }
     TCanvas *c= new TCanvas();
     gPad->SetLogy();
    hSCTimeNoPileUp->Draw();
    TCanvas *c1= new TCanvas();
    gPad->SetLogy();
    hSCTimePileUp->Draw();
     TCanvas *c2= new TCanvas();
    gPad->SetLogy();
    hSCChargePileUp->Draw();
     TCanvas *c3= new TCanvas();
    gPad->SetLogy();
    hSCChargeNoPileUp->Draw();
 }