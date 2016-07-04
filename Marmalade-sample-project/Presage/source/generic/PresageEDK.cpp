/*
Generic implementation of the PresageEDK extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "PresageEDK_internal.h"
s3eResult PresageEDKInit()
{
    //Add any generic initialisation code here
    return PresageEDKInit_platform();
}

void PresageEDKTerminate()
{
    //Add any generic termination code here
    PresageEDKTerminate_platform();
}

void PresageStart()
{
	PresageStart_platform();
}

void PresageAdToServe()
{
	PresageAdToServe_platform();
}

void PresageLoadAd()
{
	PresageLoadAd_platform();
}

void PresageShowAd()
{
	PresageShowAd_platform();
}

void PresageLaunchEula() {
	PresageLaunchEula_platform();
}
