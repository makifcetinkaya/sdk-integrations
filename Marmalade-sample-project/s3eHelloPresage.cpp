#include "s3e.h"

#include <Presage.h>
#include <IwDebug.h>

#include "ExamplesMain.h"

void AdFound(void* data) { IwTrace(Presage, ("PRESAGE AD FOUND")); }
void AdNotFound(void* data) { IwTrace(Presage, ("PRESAGE AD NOT FOUND")); }
void AdClosed(void* data) { IwTrace(Presage, ("PRESAGE AD CLOSED")); }
void AdError(void* data) { IwTrace(Presage, ("PRESAGE AD ERROR")); }
void AdDisplayed(void* data) { IwTrace(Presage, ("PRESAGE AD DISPLAYED")); }

static Button* g_ShowAdButton = 0;

void ExampleInit()
{
	Presage::start();

	AppendMessage(Presage::getStatus());

	g_ShowAdButton = NewButton("Show an Ad");
}

void ExampleTerm()
{
}

bool ExampleUpdate()
{
	g_ShowAdButton->m_Enabled = !Presage::AdInFligt() && Presage::IsAvailable();

	Button* pressed = GetSelectedButton();

	if (pressed == g_ShowAdButton&& 
		Presage::IsAvailable())
	{
		if (Presage::AdInFligt())
		{
			IwTrace(PRESAGE, ("Ad already in flight"));
		}
		else
		{
			Presage::adToServe(AdNotFound, AdFound, AdClosed, AdError, AdDisplayed, NULL);
		}
	}

	return true;
}

void ExampleRender()
{
}