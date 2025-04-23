void Histogramas(){
//------------------------------------------------
//    Canvas
//------------------------------------------------ 
	TCanvas *c = new TCanvas("c1","the fit canvas",1000,700);
	gStyle->SetTitleFont(132,"t"); 
	gStyle->SetLabelFont(132,"t");  
	gStyle->SetLegendFont(132); 
//------------------------------------------------
//    Abrir archivo
//------------------------------------------------ 
	TFile *f0 = 0x0;

	f0 = (TFile*)TFile::Open("datosTALLER.root");	
//------------------------------------------------
//    abrir histogramas
//------------------------------------------------ 	
	TH2D* hObs = (TH2D*)f0->Get("HpT");
//------------------------------------------------
//    Etiquetas
//------------------------------------------------ 
	hObs->SetTitle("Titulo");
	hObs->GetXaxis()->SetTitle("Number of Tracks");
	hObs->GetYaxis()->SetTitle("Observable"); 

	hObs->Draw();
//------------------------------------------------
//    hacer una grafica a parir de los datos
//------------------------------------------------ 
/*	const int mBin = hObs->GetNbinsX();

	//cout << "mBin: " << mBin << endl;

	double X[100] = {0};
	double Y[100] = {0};
	double eX[100] = {0};
	double eY[100] = {0};

	for( int i = 1; i < mBin; i++){

		pX[i]  = hObs->GetBinCenter(i+1);
    	pY[i]  = hObs->GetBinContent(i+1);
    	eX[i] = hObs->GetBinWidth(i+1)/2.0; 
    	eY[i] = hObs->GetBinError(i+1);	
	}

	TGraphErrors* gObs  = new TGraphErrors(mBin,X,Y,eX,eY);

	gObs->SetMarkerStyle(20); 
	gObs->SetMarkerSize(1);
	gObs->SetLineColor(kRed);
	gObs->SetMarkerColor(kRed);

	gObs->SetTitle("Titulo");
	gObs->GetXaxis()->SetTitle("Number of Tracks");
	gObs->GetYaxis()->SetTitle("Observable");

	gObs->Draw();
*/	
//------------------------------------------------
//    manipular los datos (Aquí hay un error)
//------------------------------------------------ 
/*	double nx, ny, nex, ney;
    int NP = gObs->GetN();

    double cte = 0.34;

    TGraphErrors* gObsN = new TGraphErrors();

    for(int i = 0; i < NP; i++){
        gObs->GetPoint(i, xP, yP);
        exP = gObs->GetErrorX(i);
        eyP = gObs->GetErrorY(i);

        double nyP = yP*cte;
        double enyP = eyP*cte;

        gObsN->SetPoint(i, xP, nyP);
        gObsN->SetPointError(i, exP, enyP);
    }
    gObsN->SetMarkerStyle(20);
    gObsN->SetMarkerColor(kRed+3);
    gObsN->SetLineColor(kRed+3);

    gObsN->Draw();
    */
//------------------------------------------------
//    Guardar en un archivo root
//------------------------------------------------ 
 	TFile* fOut0 = new TFile("Arch_salida.root", "RECREATE");
    fOut0->cd();
    hObs->Write("samep");
    gObs->Write("samep");
    //gObsN->Write("samep");
    fOut0->Close();


}