#ifndef Presage_h__
#define Presage_h__

class Presage
{
public:
	static bool start();

	typedef void(*AdHandler)(void* i_userData);
	typedef void(*EulaHandler)(void* i_userData);

	static void adToServe(
		AdHandler i_onAdNotFound = 0,
		AdHandler i_onAdFound = 0,
		AdHandler i_onAdClosed = 0,
		AdHandler i_onAdError = 0,
		AdHandler i_onAdDisplayed = 0,
		void*     i_userData = 0);

	static void loadAd(
		AdHandler i_onAdNotFound = 0,
		AdHandler i_onAdFound = 0,
		AdHandler i_onAdClosed = 0,
		AdHandler i_onAdError = 0,
		AdHandler i_onAdDisplayed = 0,
		void*     i_userData = 0);

	static void showAd(
		AdHandler i_onAdNotFound = 0,
		AdHandler i_onAdFound = 0,
		AdHandler i_onAdClosed = 0,
		AdHandler i_onAdError = 0,
		AdHandler i_onAdDisplayed = 0,
		void*     i_userData = 0);

	static void launchEula(
		EulaHandler i_onEulaFound = 0,
		EulaHandler i_onEulaNotFound = 0,
		EulaHandler i_onEulaClosed = 0,
		void*       i_userData = 0);

	//Will return false if Presage has not been initialized, failed to initialize
	//or the app is running on an incompatible platform (eg Marmalade simulator)
	static bool IsAvailable();

	static bool AdInFligt();
	static const char* getStatus();
};

#endif // Presage_h__
