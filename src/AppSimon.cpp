#include "lib.h"
#include "libTypes.h"
#include "libMacros.h"
#include "AppSimon.h"

#include "CtxSimon.h"
#include "CtxLogo.h"

CAppSimon	*g_TheAppSimon;

CAppSimon::CAppSimon():
CApp("AppSimon.application")
{

}

void
CAppSimon::OnPostCreate(void)
{
	Init(MAX_CTX);

	RegisterContext(CTX_LOGO_DAKIISOFT, new CCtxLogo("CtxLogoDakiisoft.context"));
	RegisterContext(CTX_LOGO_GBAX, new CCtxLogo("CtxLogoGbax2007.context"));
	RegisterContext(CTX_SIMON, new CCtxSimon("CtxSimon.context"));

	SetCurContext(CTX_LOGO_DAKIISOFT);

	CApp::OnPostCreate();
}

CApp*
newGameApp(void)
{
	return g_TheAppSimon= new CAppSimon();
}


ENTRY_POINT("Simon");
