//Contains every ROOT lib functions

#include <iostream>
#include <string>
#include <cstring>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include "do_TSomething.h"

void do_TSomething(char* filename, int total_route, Route route[]){
    printf("----Debugging----\n");
    printf("do_Tsomething func called\n");
    
    std::string s(filename);    //generates filename.root
    s = s + ".root";
    char rootfilename[25];
    strcpy(rootfilename, s.c_str());
    
    TFile* file = new TFile(rootfilename, "recreate");  //initializing TFile 
    printf("Debug: Tfile created\n");
    TTree* tree = new TTree("tree", "tree");
    
    for (int i=0;i<total_route;i++){    //fills TFile with route name and route[].total_action
        char* route_name[i][25];
        tree->Branch("Route Name", route[i].route_name);
        tree->Branch("Action", &route[i].total_action);

        tree->Fill();
    }

    TCanvas *canv = new TCanvas("canv", "Canvas", 800, 600);
    
    TH1D* histo = new TH1D("histo", "histo;Route Name;Action", total_route, 0, total_route);    //graph making
    histo->SetMinimum(0);
    histo->SetMaximum(7);
    histo->SetBarWidth(0.8);
    histo->SetBarOffset(0.1);
    histo->SetFillColor(38);

    for (int i=1;i<=total_route;i++){   //give y action, x route[].route_name
        histo->SetBinContent(i, route[i-1].total_action);
        histo->GetXaxis()->SetBinLabel(i, route[i-1].route_name);
    }

    histo->Draw("b");   //bar graph
    canv->SaveAs("Histogram.png", "");

    file->Write();
    printf("Debug: TFile written\n");
    file->Close();
}

extern "C" {    //c++ func caller
    void do_TSomething_C(char* filename, int total_route, Route route[]){
        do_TSomething(filename, total_route, route);
    }
}