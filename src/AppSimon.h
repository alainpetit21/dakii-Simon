#ifndef _SIMON_APP_H
#define _SIMON_APP_H

#include "dfcApp.h"


#define CTX_LOGO_DAKIISOFT	0
#define CTX_LOGO_GBAX		1
#define CTX_SIMON			2
#define MAX_CTX				3

class CAppSimon : public CApp
{
public:
	CAppSimon();
	virtual ~CAppSimon(){};

	virtual void OnPostCreate(void);
};

extern CAppSimon *g_TheAppSimon;

#endif //_SIMON_APP_H
