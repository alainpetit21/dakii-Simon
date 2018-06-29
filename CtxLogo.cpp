#include "lib.h"
#include "libMacros.h"
#include "libTypes.h"
#include "libMngInput.h"
#include "CtxLogo.h"
#include "AppSimon.h"


void
CCtxLogo::Activate(void)
{
	CContext::Activate();

	m_nDelayLogo= 120;
}

void
CCtxLogo::Manage(unsigned long p_nTimeTick)
{
	if(!(--m_nDelayLogo)){
		g_TheAppSimon->SetCurContext(g_TheAppSimon->GetCurContextID()+1);
		return;
	}

	CContext::Manage(p_nTimeTick);
}

