#include <Presage.h>

#include "PresageEDK.h"

#include "s3e.h"
#include <IwDebug.h>

namespace {
	Presage::AdHandler	fnOnAdNotFound = NULL;
	Presage::AdHandler	fnOnAdFound = NULL;
	Presage::AdHandler	fnOnAdClosed = NULL;
	Presage::AdHandler	fnOnAdError = NULL;
	Presage::AdHandler	fnOnAdDisplayed = NULL;

	Presage::EulaHandler fnOnEulaFound = NULL;
	Presage::EulaHandler fnOnEulaNotFound = NULL;
	Presage::EulaHandler fnOnEulaClosed = NULL;

	void*				pUserData = NULL;

	bool				bInitialised = false;
	bool				bAdInFlight = false;
	const char*			sStatus = "";


	int32 onAdNotFoundShim(void* sysData, void* usrData)
	{
		bAdInFlight = false;
		if (fnOnAdNotFound) fnOnAdNotFound(pUserData);
		return S3E_TRUE;
	}

	int32 onAdFoundShim(void* sysData, void* usrData)
	{
		bAdInFlight = false;
		if (fnOnAdFound) fnOnAdFound(pUserData);
		return S3E_TRUE;
	}

	int32 onAdClosedShim(void* sysData, void* usrData)
	{
		bAdInFlight = false;
		if (fnOnAdClosed) fnOnAdClosed(pUserData);
		return S3E_TRUE;
	}

	int32 onAdErrorShim(void* sysData, void* usrData)
	{
		bAdInFlight = false;
		if (fnOnAdClosed) fnOnAdError(pUserData);
		return S3E_TRUE;
	}

	int32 onAdDisplayedShim(void* sysData, void* usrData)
	{
		bAdInFlight = false;
		if (fnOnAdClosed) fnOnAdDisplayed(pUserData);
		return S3E_TRUE;
	}

	int32 onEulaFoundShim(void* sysData, void* usrData)
	{
		bAdInFlight = false;
		if (fnOnAdClosed) fnOnEulaFound(pUserData);
		return S3E_TRUE;
	}

	int32 onEulaNotFoundShim(void* sysData, void* usrData)
	{
		bAdInFlight = false;
		if (fnOnAdClosed) fnOnEulaNotFound(pUserData);
		return S3E_TRUE;
	}

	int32 onEulaClosedShim(void* sysData, void* usrData)
	{
		bAdInFlight = false;
		if (fnOnAdClosed) fnOnEulaClosed(pUserData);
		return S3E_TRUE;
	}
}

bool Presage::start()
{
	if (PresageEDKAvailable())
	{
		//Register callbacks here
		PresageEDKRegister(PRESAGE_RESULT_OK, onAdFoundShim, 0);
		PresageEDKRegister(PRESAGE_RESULT_NO_AD, onAdNotFoundShim, 0);
		PresageEDKRegister(PRESAGE_RESULT_CANCELLED, onAdClosedShim, 0);
		PresageEDKRegister(PRESAGE_RESULT_ERROR, onAdErrorShim, 0);
		PresageEDKRegister(PRESAGE_RESULT_DISPLAYED, onAdDisplayedShim, 0);

		PresageEDKRegister(PRESAGE_EULA_OK, onEulaFoundShim, 0);
		PresageEDKRegister(PRESAGE_NO_EULA, onEulaNotFoundShim, 0);
		PresageEDKRegister(PRESAGE_EULA_CANCELLED, onEulaClosedShim, 0);

		PresageStart();

		bInitialised = true;
	}

	return bInitialised;
}

void Presage::adToServe(AdHandler i_onAdNotFound /*= NULL*/, AdHandler i_onAdFound /*= NULL*/, AdHandler i_onAdClosed /*= NULL*/, AdHandler i_onAdError /*= NULL*/, AdHandler i_onAdDisplayed /*= NULL*/, void* i_userData /*= NULL*/)
{
	IwAssertMsg(PRESAGE, bInitialised, ("Presage has not be successfully intialised"));
	IwAssertMsg(PRESAGE, bAdInFlight == false, ("Calling adToServe before the last Ad or Eula has completed"));
	
	if (bAdInFlight) return;

	fnOnAdNotFound = i_onAdNotFound;
	fnOnAdFound = i_onAdFound;
	fnOnAdClosed = i_onAdClosed;
	fnOnAdError = i_onAdError;
	fnOnAdDisplayed = i_onAdDisplayed;
	pUserData = i_userData;

	bAdInFlight = true;
	
	PresageAdToServe();
}

void Presage::loadAd(AdHandler i_onAdNotFound /*= NULL*/, AdHandler i_onAdFound /*= NULL*/, AdHandler i_onAdClosed /*= NULL*/, AdHandler i_onAdError /*= NULL*/, AdHandler i_onAdDisplayed /*= NULL*/, void* i_userData /*= NULL*/)
{
	IwAssertMsg(PRESAGE, bInitialised, ("Presage has not be successfully intialised"));
	IwAssertMsg(PRESAGE, bAdInFlight == false, ("Calling load ad before the last Ad or Eula has completed"));
	
	if (bAdInFlight) return;

	fnOnAdNotFound = i_onAdNotFound;
	fnOnAdFound = i_onAdFound;
	fnOnAdClosed = i_onAdClosed;
	fnOnAdError = i_onAdError;
	fnOnAdDisplayed = i_onAdDisplayed;
	pUserData = i_userData;

	bAdInFlight = true;
	
	PresageLoadAd();
}

void Presage::showAd(AdHandler i_onAdNotFound /*= NULL*/, AdHandler i_onAdFound /*= NULL*/, AdHandler i_onAdClosed /*= NULL*/, AdHandler i_onAdError /*= NULL*/, AdHandler i_onAdDisplayed /*= NULL*/, void* i_userData /*= NULL*/)
{
	IwAssertMsg(PRESAGE, bInitialised, ("Presage has not be successfully intialised"));
	IwAssertMsg(PRESAGE, bAdInFlight == false, ("Calling showAd before the last Ad or Eula has completed"));
	
	if (bAdInFlight) return;

	fnOnAdNotFound = i_onAdNotFound;
	fnOnAdFound = i_onAdFound;
	fnOnAdClosed = i_onAdClosed;
	fnOnAdError = i_onAdError;
	fnOnAdDisplayed = i_onAdDisplayed;
	pUserData = i_userData;

	bAdInFlight = true;
	
	PresageShowAd();
}

void Presage::launchEula(EulaHandler i_onEulaNotFound /*= NULL*/, EulaHandler i_onEulaFound /*= NULL*/, EulaHandler i_onEulaClosed /*= NULL*/, void* i_userData /*= NULL*/)
{
	IwAssertMsg(PRESAGE, bInitialised, ("Presage has not be successfully intialised"));
	IwAssertMsg(PRESAGE, bAdInFlight == false, ("Calling launchEula before the last Ad or Eula has completed"));
	
	if (bAdInFlight) return;

	fnOnEulaNotFound = i_onEulaNotFound;
	fnOnEulaFound = i_onEulaFound;
	fnOnEulaClosed = i_onEulaClosed;
	pUserData = i_userData;

	bAdInFlight = true;
	
	PresageLaunchEula();
}

bool Presage::AdInFligt()
{
	return bAdInFlight;
}

const char* Presage::getStatus()
{
	return sStatus;
}

bool Presage::IsAvailable()
{
	return bInitialised;
}
