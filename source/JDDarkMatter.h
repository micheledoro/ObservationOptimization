/*
 * DM.h
 *
 *  Created on: 03/07/2017
 *  Authors: David Navarro Gironés 	<<david.navarro.girones@gmail.com>>
 *  		 Joaquim Palacio 		<<jpalacio@ifae.es>>
 *
 *  		 ADD A GENERAL DESCRIPTION ON THE CLASS, THE MAIN FUNCTIONS, THE VARIABLES
 *  		 AND MENTION THE "runExample#.C" THAT SHOWS HOW TO USE IT
 */

#ifndef JDDarkMatter_H_
#define JDDarkMatter_H_

#include <TF1.h>
#include <TGraph.h>
#include <TF2.h>

using namespace std;

class JDDarkMatter {
public:

	JDDarkMatter();
	JDDarkMatter(TGraph* jfactor);
	JDDarkMatter(TString txtFile);
	JDDarkMatter(TString author, TString source, TString candidate, TString mySourcePath);
	virtual ~JDDarkMatter();


	//Setters********

	void SetSourcePath(TString sourcePath) 				{sMySourcePath=sourcePath;}
	void SetSourceName(TString sourceName) 				{sSource=sourceName;}
	void SetCandidate(TString candidate) 				{sCandidate=candidate;}
	void SetAuthor(TString author) 						{sAuthor=author;}
	void SetThetaMax(Double_t thetaMax) 				{dThetaMax=thetaMax;}
	void SetIsSphericalCoordinates(Bool_t isSphericalCoordinates)				{bIsSphericalCoordinates=isSphericalCoordinates;}

	Bool_t SetJFactorFromTGraph(TGraph* jfactor, Bool_t verbose=0);//, Bool_t verbose);
	Bool_t SetJFactorFromTxtFile(TString txtFile, Bool_t verbose=0);//, Bool_t verbose);

	//Getters********

	///////////////////////////////////////////////////////
	//void
	///////////////////////////////////////////////////////
	void GetListOfCandidates();
	void GetListOfSources();
	void GetListOfAuthors();
	void GetListOfConstructors();
	void GetUnits();
	void GetWarning();
	///////////////////////////////////////////////////////
	//Int
	///////////////////////////////////////////////////////
	Int_t GetNumPointsJFactorGraph() 	{return iNumPointsJFactorGraph;}

	///////////////////////////////////////////////////////
	//TF1
	///////////////////////////////////////////////////////

	TF1* GetTF1JFactorVsTheta()
	{
		if(!GetIsJFactor()) GetWarning();
		return fEvaluateJFactorVsTheta;
	}

	TF1* GetTF1JFactor_m1VsTheta()
	{
		if(!GetIsJFactor()) GetWarning();
		return fEvaluateJFactor_m1VsTheta;
	}

	TF1* GetTF1JFactorFromLOSVsTheta()
	{
		if(!GetIsJFactor()) GetWarning();
		return fIntegrateJFactorFromLOSVsTheta;
	}


	TF1* GetTF1JFactor_m1FromLOSVsTheta()
	{
		if(!GetIsJFactor()) GetWarning();
		return fIntegrateJFactor_m1FromLOSVsTheta;
	}

	TF1* GetTF1JFactorOffFromLOSVsTheta(Double_t offset=20)
	{
		if(!GetIsJFactor()) GetWarning();
		fIntegrateJFactorOffFromLOSVsTheta->SetParameter(0,offset);
		return fIntegrateJFactorOffFromLOSVsTheta;
	}

	TF1* GetTF1JFactor_m1OffFromLOSVsTheta(Double_t offset=20)
	{
		if(!GetIsJFactor()) GetWarning();
		fIntegrateJFactor_m1OffFromLOSVsTheta->SetParameter(0,offset);
		return fIntegrateJFactor_m1OffFromLOSVsTheta;
	}

	TF1* GetTF1LOSVsTheta()
	{
		if(!GetIsJFactor()) GetWarning();
		return fEvaluateLOSVsTheta;
	}

	TF1* GetTF1LOS_m1VsTheta()
	{
		if(!GetIsJFactor()) GetWarning();
		return fEvaluateLOS_m1VsTheta;
	}

	TF1* GetTF1NormLOSVsTheta(Double_t normTheta)
	{
		if(!GetIsJFactor()) GetWarning();
		fEvaluateNormLOSVsTheta->SetParameter(0,normTheta);
		return fEvaluateNormLOSVsTheta;
	}

	TF1* GetTF1NormLOS_m1VsTheta(Double_t normTheta)
	{
		if(!GetIsJFactor()) GetWarning();
		fEvaluateNormLOS_m1VsTheta->SetParameter(0,normTheta);
		return fEvaluateNormLOS_m1VsTheta;
	}

	///////////////////////////////////////////////////////
	//TF2
	///////////////////////////////////////////////////////

	TF2* GetTF2LOSThetaVSThetaPhi()
	{
		if(!GetIsJFactor()) GetWarning();
		return fEvaluateLOSThetaVsThetaPhi;
	}

	TF2* GetTF2LOS_m1ThetaVSThetaPhi()
	{
		if(!GetIsJFactor()) GetWarning();
		return fEvaluateLOS_m1ThetaVsThetaPhi;
	}

	TF2* GetTF2LOSOffThetaVSThetaPhi()
	{
		if(!GetIsJFactor()) GetWarning();
		return fEvaluateLOSOffThetaVsThetaPhi;
	}

	TF2* GetTF2LOS_m1OffThetaVSThetaPhi()
	{
		if(!GetIsJFactor()) GetWarning();
		return fEvaluateLOS_m1OffThetaVsThetaPhi;
	}



	///////////////////////////////////////////////////////
	//Double_t
	///////////////////////////////////////////////////////

	Double_t GetThetaMax() 		{return dThetaMax;}			// [deg]
	Double_t GetJFactorMax() 	{return dJFactorMax;}		// [~GeV,~cm]
	Double_t GetJFactorMin() 	{return dJFactorMin;}		// [~GeV,~cm]


	///////////////////////////////////////////////////////
	//TString
	///////////////////////////////////////////////////////

	TString GetAuthor()			{return sAuthor;}
	TString GetCandidate()		{return sCandidate;}
	TString GetSourcePath() 	{return sMySourcePath;}
	TString GetSourceName() 	{return sSource;}

	///////////////////////////////////////////////////////
	//Bool_t
	///////////////////////////////////////////////////////

	Bool_t GetIsBonnivard() 					{return bIsBonnivard;}
	Bool_t GetIsGeringer() 						{return bIsGeringer;}
	Bool_t GetIsJFactor()						{return bIsJFactor;}
	Bool_t GetIsSphericalCoordinates()			{return bIsSphericalCoordinates;}

protected:

	//Setters********
	void SetIsBonnivard(Bool_t isBonnivard) 			{bIsBonnivard=isBonnivard;}
	void SetIsGeringer(Bool_t isGeringer) 				{bIsGeringer=isGeringer;}
	void SetIsJFactor(Bool_t isJFactor)					{bIsJFactor=isJFactor;}
	void SetNumPointsJFactorGraph(Int_t numPoints) 		{iNumPointsJFactorGraph=numPoints;}

	void SetJFactorMax(Double_t jFactorMax) 			{dJFactorMax=jFactorMax;}
	void SetJFactorMin(Double_t jFactorMin) 			{dJFactorMin=jFactorMin;}

	Bool_t SetJFactorFromReferences(Bool_t verbose=0);

	//OTHERS********

	void CreateFunctionsDM();
	void ReadJFactorBonnivard(Bool_t verbose=0); //is_m1=0 -> JFactor; is_m1=1 -> JFactor_m1
	void ReadJFactorGeringer(Bool_t verbose=0);

	Double_t TGraphEvaluateJFactorVsTheta(Double_t* x, Double_t* par);
	Double_t TGraphEvaluateJFactor_m1VsTheta(Double_t* x, Double_t* par);

	Double_t IntegrateJFactorFromLOSVsTheta(Double_t* x, Double_t* par);
	Double_t IntegrateJFactor_m1FromLOSVsTheta(Double_t* x, Double_t* par);

	Double_t IntegrateJFactorOffFromLOSVsTheta(Double_t* x, Double_t* par);
	Double_t IntegrateJFactor_m1OffFromLOSVsTheta(Double_t* x, Double_t* par);

	Double_t EvaluateLOSVsTheta(Double_t* x, Double_t* par);
	Double_t EvaluateLOS_m1VsTheta(Double_t* x, Double_t* par);

	Double_t EvaluateNormLOSVsTheta(Double_t* x, Double_t* par);
	Double_t EvaluateNormLOS_m1VsTheta(Double_t* x, Double_t* par);

	Double_t EvaluateQFactorVsTheta(Double_t* x, Double_t* par);


	Double_t EvaluateLOSThetaVsThetaPhi(Double_t* x, Double_t* par);
	Double_t EvaluateLOS_m1ThetaVsThetaPhi(Double_t* x, Double_t* par);

	Double_t EvaluateLOSOffThetaVsThetaPhi(Double_t* x, Double_t* par);
	Double_t EvaluateLOS_m1OffThetaVsThetaPhi(Double_t* x, Double_t* par);

private:

	///////////////////////////////////////////////////////
	//TString
	///////////////////////////////////////////////////////

	TString sAuthor;
	TString sSource;
	TString sCandidate;
	TString sMySourcePath;

	///////////////////////////////////////////////////////
	//Int_t
	///////////////////////////////////////////////////////

	Int_t iNumPointsJFactorGraph;

	///////////////////////////////////////////////////////
	//Double_t
	///////////////////////////////////////////////////////

	Double_t dThetaMax;
	Double_t dJFactorMax;
	Double_t dJFactorMin;

	Double_t dDeg2Rad;

	///////////////////////////////////////////////////////
	//TGraph
	///////////////////////////////////////////////////////

	// (QUIM) you can specify here how this JFactor is going to be filled,
	// make explicit that the same TGraph is used for Bon/Ger & Ann/Dec
	TGraph* gJFactor;
	TGraph* gJFactor_m1;

	///////////////////////////////////////////////////////
	//TF1
	///////////////////////////////////////////////////////

	TF1* fEvaluateJFactorVsTheta;
	TF1* fEvaluateJFactor_m1VsTheta;

	TF1* fEvaluateLOSVsTheta;
	TF1* fEvaluateLOS_m1VsTheta;

	TF1* fEvaluateNormLOSVsTheta;
	TF1* fEvaluateNormLOS_m1VsTheta;

	TF1* fIntegrateJFactorFromLOSVsTheta;
	TF1* fIntegrateJFactor_m1FromLOSVsTheta;

	TF1* fIntegrateJFactorOffFromLOSVsTheta;
	TF1* fIntegrateJFactor_m1OffFromLOSVsTheta;

	TF1* fEvaluateQFactorVsTheta;

	///////////////////////////////////////////////////////
	//TF2
	///////////////////////////////////////////////////////

	TF2* fEvaluateLOSThetaVsThetaPhi;
	TF2* fEvaluateLOS_m1ThetaVsThetaPhi;

	TF2* fEvaluateLOSOffThetaVsThetaPhi;
	TF2* fEvaluateLOS_m1OffThetaVsThetaPhi;

	///////////////////////////////////////////////////////
	//Bool_t
	///////////////////////////////////////////////////////

	Bool_t bIsBonnivard;
	Bool_t bIsGeringer;
	Bool_t bIsJFactor;
	Bool_t bIsSphericalCoordinates;
};



#endif /* JDDarkMatter_H_ */
