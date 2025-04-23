#include "TH1.h"
#include "TCanvas.h"
void hist() {
   //create a fix bin histogram
   TH1F *h = new TH1F("h","test rebin",100,-3,3);
   Int_t nentries = 1000;
   h->FillRandom("gaus",nentries);

   TCanvas *c1 = new TCanvas("c1","c1",800,1000);
   h->Draw();
}   