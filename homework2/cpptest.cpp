#include <iostream>
#include <string>
#include <cstring>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

#define TXT_LENGTH 25

typedef struct {
    char route_name[TXT_LENGTH];
    double total_action;
} Route;

void do_TSomething(char* filename, int total_route, Route route[]){
    printf("----Debugging----\n");
    printf("do_Tsomething func called\n");
    
    std::string s(filename);
    s = s + ".root";
    char rootfilename[25];
    strcpy(rootfilename, s.c_str());
    
    TFile* file = new TFile(rootfilename, "recreate");
    printf("Debug: Tfile created\n");
    TTree* tree = new TTree("tree", "tree");
    
    for (int i=0;i<total_route;i++){
        char* route_name[i][25];
        tree->Branch("Route Name", route[i].route_name);
        tree->Branch("Action", &route[i].total_action);

        tree->Fill();
    }

    TH1D* histo = new TH1D("histo", "histo;Route Name;Action", total_route, 0, total_route);
    histo->SetMinimum(0);
    histo->SetMaximum(7);

    for (int i=1;i<=total_route;i++){
        histo->SetBinContent(i, route[i-1].total_action);
        histo->GetXaxis()->SetBinLabel(i, route[i-1].route_name);
    }

    histo->Draw("b");

    file->Write();
    printf("Debug: TFile written\n");
    file->Close();
}

int main(){
    printf("----Debugging----\n");
    Route route[2];

    sprintf(route[0].route_name, "Route 1");
    route[0].total_action = 4.0134;

    sprintf(route[1].route_name, "Route 2");
    route[1].total_action = 3.5848;

    for (int i=0;i<2;i++){
        printf("#%d Route Name: %s Action: %f\n", i, route[i].route_name, route[i].total_action);
    }
   
    char rootfilename[9] = "roottest";

    do_TSomething(rootfilename, 2, route);

    return 0;
}