/*
 * JDDarkMatter.h
 *
 *  Created on: 03/07/2017
 *  Last revision: 09/09/2020
 *
 *  Authors: 
 *   David Navarro Gironés 	<<david.navarro.girones@gmail.com>>
 *   Joaquim Palacio 		<<jpalacio@ifae.es>>
 *
 *  THIS CLASS IS THE ONE RELATED WITH THE DARK MATTER DATA.
 *  WITH THIS CLASS YOU CAN EVALUATE THE JFACTOR VS THETA, 
 * THE LOS VS THETA AND PHI, THE JFACTOR OBTAINED BY INTEGRATING THE LOS.
 * 
 *  VARIABLES:
 *  	THETA 	[DEG]
 *  	PHI	  	[RAD]
 *  	OFFSET	[DEG]
 *  The macro "macros/exampleJDDarkMatter.cxx" shows how to use this class.
 */

#include "JDDarkMatter.h"

#include <TGraph.h>
#include <TMath.h>
#include <Rtypes.h>
#include <stddef.h>
#include <fstream>
#include <iostream>
#include <Rtypes.h>
#include <TAttFill.h>
#include <TAttLine.h>
#include <TAttText.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TF2.h>
#include <TGraph.h>
#include <TH1.h>
#include <TLegend.h>
#include <TPave.h>
#include <TString.h>
#include <TVirtualPad.h>
#include <TStyle.h>

using namespace std;

static const Double_t SolarMass2GeV = 1.1154e57;  			// [GeV/SolarM]
static const Double_t kpc2cm        = 3.08568e21; 			// [cm/kpc]


//-----------------------------------------------
//
// This is the constructor used to show the possibilities that offers the JDDarkMatter class
// It redirects us to CreateFunctionDM()
JDDarkMatter::JDDarkMatter():
  sSource(""), sMySourcePath (""),
  sAuthor(""), sCandidate(""), gJFactor(NULL),
  fEvaluateJFactorVsTheta(NULL), fEvaluateJFactorSigma1VsTheta(NULL),
  bIsBonnivard(0),bIsGeringer(0),bIsJFactor(0),
  dDeg2Rad(TMath::Pi()/180.), dBinResolution(0.05)
{
  cout << endl;
  cout << endl;
  cout << "   Constructor JDDarkMatter..." << endl;
  cout << endl;
  cout << endl;
  
  CreateFunctionsDM();
}

//-----------------------------------------------
//
// This is the constructor used when the data is given by a TGraph
// It redirects us to CreateFunctionDM()
JDDarkMatter::JDDarkMatter(TGraph* jfactor):
  sSource(""), sMySourcePath (""),
  sAuthor(""), sCandidate(""), gJFactor(NULL),
  fEvaluateJFactorVsTheta(NULL), fEvaluateJFactorSigma1VsTheta(NULL),
  bIsBonnivard(0),bIsGeringer(0),bIsJFactor(0),
  dDeg2Rad(TMath::Pi()/180.), dBinResolution(0.05)
{
  cout << endl;
  cout << endl;
  cout << "   Constructor JDDarkMatter..." << endl;
  cout << endl;
  cout << endl;
  
  if(!SetJFactorFromTGraph(jfactor))
    {
      cout << "   ***********************************" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***   JFactor could not be set  ***" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***********************************" << endl;
      return;
      
    }
  
  CreateFunctionsDM();
  //CreateFunctionsAP();
  
  if(!SetdNdOmegaFromJFactor())
    {
      cout << "   ***********************************" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***  dN/dOmega could not be set ***" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***********************************" << endl;
      return;
    }
}

//-----------------------------------------------
//
// This is the constructor used when the data is given by a txtFile
// It redirects us to CreateFunctionDM()
JDDarkMatter::JDDarkMatter(TString txtFile):
  sSource(""), sMySourcePath (""),
  sAuthor(""), sCandidate(""), gJFactor(NULL),
  fEvaluateJFactorVsTheta(NULL), fEvaluateJFactorSigma1VsTheta(NULL),
  bIsBonnivard(0),bIsGeringer(0),bIsJFactor(0),
  dDeg2Rad(TMath::Pi()/180.), dBinResolution(0.05)
{
  cout << endl;
  cout << endl;
  cout << "   Constructor JDDarkMatter..." << endl;
  cout << endl;
  cout << endl;
  
  if(!SetJFactorFromTxtFile(txtFile))
    {
      cout << "   ***********************************" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***   JFactor could not be set  ***" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***********************************" << endl;
      return;
      
    }
  
  CreateFunctionsDM();
  //CreateFunctionsAP();

  if(!SetdNdOmegaFromJFactor())
    {
      cout << "   ***********************************" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***  dN/dOmega could not be set ***" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***********************************" << endl;
      return;
    }
}


//-----------------------------------------------
//
// This is the constructor used when the references are used.
//
// Possible variables are:
// sAuthor 	= (TString) name of author
// sSource 	= (TString) name of dark matter halo
// sCandidate 	= (TString) type of signal
//  sMyPath     = (TString) name of the path			This is the path where the data is located
//
// It redirects us to CreateFunctionDM()
JDDarkMatter::JDDarkMatter(TString author,
			   TString source,
			   TString candidate,
			   TString mySourcePath):
  sAuthor(author), sSource(source), sCandidate(candidate), sMySourcePath (mySourcePath),
  gJFactor(NULL), fEvaluateJFactorVsTheta(NULL),
  bIsBonnivard(0),bIsGeringer(0),bIsJFactor(0), 
  dDeg2Rad(TMath::Pi()/180.), dBinResolution(0.05)
{
  cout << endl;
  cout << endl;
  cout << "   Constructor JDDarkMatter..." << endl;
  cout << endl;
  cout << endl;
  
  if(!SetJFactorFromReferences())
    {
      cout << "   ****************************************************" << endl;
      cout << "   ***                                              ***" << endl;
      cout << "   ***   JFactor could not be read from references  ***" << endl;
      cout << "   ***                                              ***" << endl;
      cout << "   ****************************************************" << endl;
      return;
    }
  
  CreateFunctionsDM();
  //CreateFunctionsAP();
  
  if(!SetdNdOmegaFromJFactor())
    {
      cout << "   ***********************************" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***  dN/dOmega could not be set ***" << endl;
      cout << "   ***                             ***" << endl;
      cout << "   ***********************************" << endl;
      return;
    }
  
}

//-----------------------------------------------
//
//  This is the destructor.
//  It deletes the functions in order not to be reused
JDDarkMatter::~JDDarkMatter()
{

  if (gJFactor)		               delete gJFactor;
  if (fEvaluateJFactorVsTheta)	       delete fEvaluateJFactorVsTheta;
  if (fEvaluateJFactorSigma1VsTheta)   delete fEvaluateJFactorSigma1VsTheta;

  cout << endl;
  cout << endl;
  cout << "   Destructor JDDarkMatter..." << endl;
  cout << endl;
  cout << endl;
}

//-----------------------------------------------
// This function creates the important functions of this class. The functions are:
//  TF1 fEvaluateJFactorVsTheta: evaluates the JFactor vs Theta;
//    JFactor [~GeV,~cm] theta [deg]
//  TF1 fEvaluateJFactorSigma1VsTheta: 	evaluates the JFactorSigma1 (Uncertainty:
//    JFactor less sigma) vs Theta; JFactor [~GeV,~cm]     theta [deg]
void JDDarkMatter::CreateFunctionsDM()
{

  fEvaluateJFactorVsTheta = new TF1("fEvaluateJFactorVsTheta",this,&JDDarkMatter::TGraphEvaluateJFactorVsTheta,0.,GetThetaMax(),0,"JDDarkMatter","TGraphEvaluateJFactorVsTheta");
  fEvaluateJFactorSigma1VsTheta = new TF1("fEvaluateJFactorSigma1VsTheta",this,&JDDarkMatter::TGraphEvaluateJFactorSigma1VsTheta,0.,GetThetaMax(),0,"JDDarkMatter","TGraphEvaluateJFactorSigma1VsTheta");
}

//-----------------------------------------------
//
// This boolean is TRUE(1) if the JFactor can be read and FALSE(0) if the JFactor can not be read
// It fills a TGraph with the data given by the user with another TGraph
// It sets the maximum and minimum value of the JFactor and the maximum value of theta
// If the process is correct, the boolean SetIsJFactor is TRUE
Bool_t JDDarkMatter::SetJFactorFromTGraph(TGraph* jfactor, Bool_t verbose)
{

  gJFactor =jfactor;
  
  SetNumPointsJFactorGraph((Int_t)gJFactor->GetN());
  if(GetNumPointsJFactorGraph()<=0) return 0;
  
  Int_t numPoint = GetNumPointsJFactorGraph();
  SetJFactorMin(gJFactor->GetY()[0]);
  SetJFactorMax(gJFactor->GetY()[numPoint-1]);
  SetThetaMin(gJFactor->GetX()[0]);
  SetThetaMax(gJFactor->GetX()[numPoint-1]);
  
  if (verbose==1)
    for(Int_t i=0; i<numPoint;i++){
      cout << gJFactor->GetX()[i] << " " << gJFactor->GetY()[i] << endl;
    }
  
  SetIsJFactor(1);
  return 1;
}

//-----------------------------------------------
//
// This boolean is TRUE(1) if the JFactor can be read and FALSE(0) if the JFactor can not be read
//  It fills a TGraph with the data given by the user with a txtFile
//  It sets the maximum and minimum value of the JFactor and the maximum value of theta
//  If the process is correct, the boolean SetIsJFactor is TRUE
Bool_t JDDarkMatter::SetJFactorFromTxtFile(TString txtFile, Bool_t verbose)
{
  Double_t theta, dJ;
  Int_t contador=0;
  
  gJFactor = new TGraph();
  
  while(contador==0)
    {
      gJFactor->SetPoint(contador,0.,0.);
      contador ++;
    }
  
  ifstream file (txtFile);
  while(file >> theta >> dJ)
    {
      // only for Tests
      if (verbose==1)	cout << theta << " " << dJ << endl;
      gJFactor->SetPoint(contador,theta,dJ);
      if(contador==1) SetJFactorMin(dJ);
      contador ++;
    }
  
  SetNumPointsJFactorGraph(contador);
  SetJFactorMax(dJ);
  SetThetaMax(theta);
  file.close();
  
  if(GetNumPointsJFactorGraph()<=0) return 0;
  
  SetIsJFactor(1);
  return 1;
}

//-----------------------------------------------
// This boolean is TRUE(1) if the JFactor can be read and FALSE(0) if the JFactor can not be read
//  It creates the two ReadJFactor functions, depending on the author.
//  If the process is correct, the boolean SetIsBonnivard(Geringer) is TRUE(FALSE)
//  It redirects to other function depending on which author we are taking into account.
Bool_t JDDarkMatter::SetJFactorFromReferences(Bool_t verbose)
{

  if (GetAuthor() == "Bonnivard")
    {
      cout << "   "<< endl;
      cout << "   Reading JFactor from: "<< endl;
      cout << "   Dark matter annihilation and decay in dwarf spheroidal galaxies: The classical and ultrafaint dSphs" << endl;
      cout << "   Bonnivard et al., " << endl;
      cout << "   https://arxiv.org/abs/1504.02048" << endl;
      cout << "   "<< endl;
      
      SetIsBonnivard(1);
      
      ReadJFactorBonnivard();
      return 1;
    }
  else if (GetAuthor() == "Geringer")
    {
      cout << "   "<< endl;
      cout << "   Reading JFactor from: "<< endl;
      cout << "   Dwarf galaxy annihilation and decay emission profiles for dark matter experiments" << endl;
      cout << "   Geringer-Sameth et al., " << endl;
      cout << "   https://arxiv.org/abs/1408.0002" << endl;
      cout << "   "<< endl;
      
      SetIsGeringer(1);
      
      ReadJFactorGeringer();
      return 1;
    }
  
  return 0;
}

//-----------------------------------------------
// Set dN/dOmega from JFactor
Bool_t JDDarkMatter::SetdNdOmegaFromJFactor(){
  
  gdNdOmega = new TGraph();
  if(GetIsJFactorSigma1()){gdNdOmegaSigma1 = new TGraph();}
  
  
  Double_t thetaMin = GetThetaMin();
  Double_t thetaMax = GetThetaMax();
  
  Int_t numPoints = GetNumPointsJFactorGraph();
  for(Int_t i=1; i<numPoints;i++)
    {
      Double_t theta = thetaMin + (thetaMax-thetaMin)/(numPoints*1.)*i;
      //		cout << thetaMin << " " << thetaMax << endl;
      Double_t dNdOmega = fEvaluateJFactorVsTheta->Derivative(theta)/(2*TMath::Pi()*TMath::Sin(theta*dDeg2Rad));
      
      gdNdOmega->SetPoint(i,theta,dNdOmega);
      //		cout << theta << " " << dNdOmega << endl;
      if(GetIsJFactorSigma1())
	{
	  Double_t dNdOmegaSigma1 = fEvaluateJFactorSigma1VsTheta->Derivative(theta)/(2*TMath::Pi()*TMath::Sin(theta*dDeg2Rad));
	  gdNdOmegaSigma1->SetPoint(i,theta,dNdOmegaSigma1);
	}
    }
  
  SetIsdNdOmega(1);
  if(GetIsJFactorSigma1()){SetIsdNdOmegaSigma1(1);}
  
  return 1;
}

//-----------------------------------------------
// This function reads the JFactor data from Bonnivard
// It fulfills the TGraph gJFactor (number of points, theta [deg], JFactor[~GeV, ~cm])
// with this data
// It fulfills the TGraph gJFactorSigma1 (number of points, theta [deg], JFactorSigma1
// [~GeV, ~cm]) with this data
// It sets the maximum and minimum value of the JFactor and the maximum value of theta
// It allows to distinguish between Decay or Annihilation
void JDDarkMatter::ReadJFactorBonnivard(Bool_t verbose)
{
  Int_t contador = 0;
  
  gJFactor = new TGraph();
  gJFactorSigma1 = new TGraph();
  
  Double_t dJ, dJSigma1, dJ_p1, dJ_m2, dJ_p2;
  Double_t theta; // [deg]
  
  if (verbose==1)
    {
      cout << " " << endl;
      cout << "    GetSourcePath() = " << GetSourcePath() << endl;
      cout << " " << endl;
    }
  
  if (GetCandidate() == "Decay")
    {
      while(contador==0)
	{
	  gJFactor->SetPoint(contador,0.,0.);
	  gJFactorSigma1->SetPoint(contador,0.,0.);
	  contador ++;
	}
      
      ifstream file (GetSourcePath()+"/references/JFactor/Bonnivard/"+GetSourceName()+"_Dalphaint_cls_READ.output");
      while(file >> theta >> dJ >> dJSigma1 >> dJ_p1 >> dJ_m2 >> dJ_p2)
	{
	  gJFactor->SetPoint(contador,theta,(dJ*(TMath::Power(SolarMass2GeV,1.)/TMath::Power(kpc2cm,2.))));
	  gJFactorSigma1->SetPoint(contador,theta,(dJSigma1*(TMath::Power(SolarMass2GeV,1.)/TMath::Power(kpc2cm,2.))));
	  
	  // only for Tests
	  if (verbose==1) cout << theta << " " << dJ*(TMath::Power(SolarMass2GeV,1.)/TMath::Power(kpc2cm,2.)) << endl;
	  if (verbose==1) cout << theta << " " << dJSigma1*(TMath::Power(SolarMass2GeV,1.)/TMath::Power(kpc2cm,2.)) << endl;
	  
	  if(contador==1) SetJFactorMin(dJ*(TMath::Power(SolarMass2GeV,1.)/TMath::Power(kpc2cm,2.)));
	  if(contador==1) SetJFactorSigma1Min(dJSigma1*(TMath::Power(SolarMass2GeV,1.)/TMath::Power(kpc2cm,2.)));
	  
	  if(contador==1) SetThetaMin(theta);
	  contador ++;
	}
      
      SetNumPointsJFactorGraph(contador);
      SetJFactorMax(dJ*(TMath::Power(SolarMass2GeV,1.)/TMath::Power(kpc2cm,2.)));
      SetThetaMax(theta);
      file.close();
      SetIsJFactor(1);
      SetIsJFactorSigma1(1);
    }
  
  else if(GetCandidate() == "Annihilation")
    {
      
      while(contador==0)
	{
	  gJFactor->SetPoint(contador,0.,0.);
	  gJFactorSigma1->SetPoint(contador,0.,0.);
	  contador ++;
	}
      
      ifstream file (GetSourcePath()+"/references/JFactor/Bonnivard/"+GetSourceName()+"_Jalphaint_cls_READ.output");
      while(file >> theta >> dJ >> dJSigma1 >> dJ_p1 >> dJ_m2 >> dJ_p2)
	{
	  gJFactor->SetPoint(contador,theta,(dJ*(TMath::Power(SolarMass2GeV,2.)/TMath::Power(kpc2cm,5.))));
	  gJFactorSigma1->SetPoint(contador,theta,(dJSigma1*(TMath::Power(SolarMass2GeV,2.)/TMath::Power(kpc2cm,5.))));
	  
	  // only for Tests
	  if (verbose==1) cout << theta << " " << dJ*(TMath::Power(SolarMass2GeV,2.)/TMath::Power(kpc2cm,5.)) << endl;
	  if (verbose==1) cout << theta << " " << dJSigma1*(TMath::Power(SolarMass2GeV,2.)/TMath::Power(kpc2cm,5.)) << endl;
	  
	  if(contador==1) SetJFactorMin(dJ*(TMath::Power(SolarMass2GeV,2.)/TMath::Power(kpc2cm,5.)));
	  if(contador==1) SetJFactorSigma1Min(dJSigma1*(TMath::Power(SolarMass2GeV,2.)/TMath::Power(kpc2cm,5.)));
	  
	  if(contador==1) SetThetaMin(theta);
	  
	  contador ++;
	}
      
      SetNumPointsJFactorGraph(contador);
      SetJFactorMax(dJ*(TMath::Power(SolarMass2GeV,2.)/TMath::Power(kpc2cm,5.)));
      SetThetaMax(theta);
      file.close();
      SetIsJFactor(1);
      SetIsJFactorSigma1(1);
    }
  
  else
    {
      cout<<"ERROR: Candidate not valid"<<endl;
      cout<<"Possibilities are: DECAY or ANNIHILATION"<<endl;
    }
  
}

//-----------------------------------------------
//	This function reads the JFactor data from Geringer
//	It fulfills the gJFactor TGraph (number of points, theta [deg], JFactor[~GeV, ~cm])
//	It fulfills the gJFactorSigma1 TGraph (number of points, theta [deg], JFactorSigma1[~GeV, ~cm])
//	It sets the maximum and minimum value of the JFactor and the maximum value of theta
//	It allows to distinguish between Decay or Annihilation
void JDDarkMatter::ReadJFactorGeringer(Bool_t verbose)
{
  Int_t contador = 0;
  
  if (verbose==1)
    {
      cout << " " << endl;
			cout << "    GetSourcePath() = " << GetSourcePath() << endl;
			cout << " " << endl;
		}

	gJFactor = new TGraph();
	gJFactorSigma1 = new TGraph();

	TString name;
	Double_t LogJann2m, LogJann1m, LogJann, LogJann1p, LogJann2p;
	Double_t LogJdec2m, LogJdec1m, LogJdec, LogJdec1p, LogJdec2p;
	Double_t a,b,c,d,e,f,g,h,i,j;
	Double_t theta; // [deg]
	
	while(contador==0)
	  {
	    gJFactor->SetPoint(contador,0.,0.);
	    gJFactorSigma1->SetPoint(contador,0.,0.);
	    contador ++;
	  }
	
	ifstream file (GetSourcePath()+"/references/JFactor/GeringerSameth/GeringerSamethTable_"+GetSourceName()+".txt");
	while(file	>> name >> theta
	      >> LogJann2m >> LogJann1m >> LogJann >> LogJann1p >> LogJann2p
	      >> LogJdec2m >> LogJdec1m >> LogJdec >> LogJdec1p >> LogJdec2p
	      >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j)
	  {
	    if(GetCandidate() == "Decay")
	      {
		if(contador==1) SetJFactorMin(TMath::Power(10., LogJdec));
		if(contador==1) SetJFactorSigma1Min(TMath::Power(10., LogJdec1m));
		gJFactor->SetPoint(contador, theta, TMath::Power(10., LogJdec));
		gJFactorSigma1->SetPoint(contador, theta, TMath::Power(10., LogJdec1m));
		
		// only for Tests
		if (verbose==1) cout << theta << " " << TMath::Power(10., LogJdec)<< endl;
		if (verbose==1) cout << theta << " " << TMath::Power(10., LogJdec1m)<< endl;
	      }
	    
	    else if (GetCandidate() == "Annihilation")
	      {
		if(contador==1) SetJFactorMin(TMath::Power(10., LogJann));
		if(contador==1) SetJFactorSigma1Min(TMath::Power(10., LogJann1m));
		gJFactor->SetPoint(contador, theta, TMath::Power(10., LogJann));
		gJFactorSigma1->SetPoint(contador, theta, TMath::Power(10., LogJann1m));
		
		// only for Tests
		if (verbose==1) cout << theta << " " << TMath::Power(10., LogJann)<< endl;
		if (verbose==1) cout << theta << " " << TMath::Power(10., LogJann1m)<< endl;
	      }
	    else
	      {
		cout<<"ERROR: Candidate is not valid"<<endl;
		cout<<"Possibilities are: DECAY or ANNIHILATION"<<endl;
		break;
	      }
	    
	    if(contador==1) SetThetaMin(theta);
	    contador ++;
	  }
	SetNumPointsJFactorGraph(contador);
	if(GetCandidate()== "Decay"){SetJFactorMax(TMath::Power(10., LogJdec));}
	else if (GetCandidate()=="Annihilation"){SetJFactorMax(TMath::Power(10., LogJann));}
	SetThetaMax(theta);
	file.close();
	SetIsJFactor(1);
	SetIsJFactorSigma1(1);
}

//-----------------------------------------------
// It evaluates the TGraph JFactor [~GeV, ~cm] vs Theta [deg]
//
// x[0] 	= dTheta [deg]
Double_t JDDarkMatter::TGraphEvaluateJFactorVsTheta(Double_t* x, Double_t* par)
{
  return gJFactor->Eval(x[0]);
}

//-----------------------------------------------
// It evaluates the TGraph JFactorSigma1 [~GeV, ~cm] vs Theta [deg]
//
// x[0] 	= dTheta [deg]
Double_t JDDarkMatter::TGraphEvaluateJFactorSigma1VsTheta(Double_t* x, Double_t* par)
{
  return gJFactorSigma1->Eval(x[0]);
}

//It shows the list of candidates
void JDDarkMatter::GetListOfCandidates()
{
  cout << " " << endl;
  cout << "    List of available candidates is:" << endl;
  cout << "    	- Annihilation" << endl;
  cout << "    	- Decay" << endl;
  cout << " " << endl;
  
}

//It shows the list of sources
void JDDarkMatter::GetListOfSources()
{
  if(GetAuthor()=="Bonnivard")
    {
      cout << " " << endl;
      cout << "    List of available sources for Bonnivard is:" << endl;
      cout << "    	- boo1" << endl;
      cout << "    	- car" << endl;
      cout << "    	- coma" << endl;
      cout << "    	- cvn1" << endl;
      cout << "    	- cvn2" << endl;
      cout << "    	- for" << endl;
      cout << "    	- her" << endl;
      cout << "    	- leo1" << endl;
      cout << "    	- leo2" << endl;
      cout << "    	- leo4" << endl;
      cout << "    	- leo5" << endl;
      cout << "    	- leot" << endl;
      cout << "    	- scl" << endl;
      cout << "    	- seg1" << endl;
      cout << "    	- seg2" << endl;
      cout << "    	- sex" << endl;
      cout << "    	- uma1" << endl;
      cout << "    	- uma2" << endl;
      cout << "    	- umi" << endl;
      cout << "    	- wil1" << endl;
      cout << " " << endl;
    }
  else if(GetAuthor()=="Geringer")
    {
      cout << " " << endl;
      cout << "    List of available sources for Geringer-Sameth is:" << endl;
      cout << "    	- Bootes" << endl;
      cout << "    	- Carina" << endl;
      cout << "    	- Coma Berenice" << endl;
      cout << "    	- Canes Venatici I" << endl;
      cout << "    	- Canes Venatici II" << endl;
      cout << "    	- Draco" << endl;
      cout << "    	- Fornax" << endl;
      cout << "    	- Hercules" << endl;
      cout << "    	- Leo I" << endl;
      cout << "    	- Leo II" << endl;
      cout << "    	- Leo IV" << endl;
      cout << "    	- Leo V" << endl;
      cout << "    	- Leo T" << endl;
      cout << "    	- Sculptor" << endl;
      cout << "    	- Segue 1" << endl;
      cout << "    	- Sextans" << endl;
      cout << "    	- Ursa Major I" << endl;
      cout << "    	- Ursa Major II" << endl;
      cout << "    	- Ursa Minor" << endl;
      cout << " " << endl;
    }
  else
    {
      cout << " " << endl;
      cout << "    Author not defined, no sources available." << endl;
      GetListOfAuthors();
    }
}

//It shows the list of authors
void JDDarkMatter::GetListOfAuthors()
{
  cout << " " << endl;
  cout << "    List of available authors is:" << endl;
  cout << "    	- Bonnivard" << endl;
  cout << "    	- Geringer" << endl;
  cout << " " << endl;
}

//It shows the units used
void JDDarkMatter::GetUnits()
{
  cout << " " << endl;
  cout << "    All units are given in:" << endl;
  cout << "    	- ~GeV" << endl;
  cout << "    	- ~cm" << endl;
  cout << "    	- ~deg" << endl;
  cout << " " << endl;
}

//It shows the available constructors
void JDDarkMatter::GetListOfConstructors()
{
  cout << " " << endl;
  cout << "    List of available constructors is:" << endl;
  cout << "    	- 	JDDarkMatter()" << endl;
  cout << "    	- 	JDDarkMatter(TGraph* jfactor)" << endl;
  cout << "    	- 	JDDarkMatter(TString txtFile)" << endl;
  cout << "    	- 	JDDarkMatter(TString author, TString source, TString candidate, TString mySourcePath)" << endl;
  cout << " " << endl;
}

//It shows a warning message if anything is wrong
void JDDarkMatter::GetWarning()
{
  cout << "  *****************************" << endl;
  cout << "  ***" << endl;
  cout << "  ***  WARNING:" << endl;
  cout << "  ***" << endl;
  cout << "  ***  	- 	JFactor not defined..." << endl;
  cout << " " << endl;
  cout << "  *****************************" << endl;
}
