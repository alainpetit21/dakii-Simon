#ifndef CTX_SIMON_H
#define CTX_SIMON_H

#include "dfcContext.h"
#include "dfcEntity.h"
#include "dfc3DEntity.h"
#include "dfcLabel.h"
#include "dfcSound.h"

class CCtxSimon : public CContext
{
public:
	CCtxSimon(const char* p_pRes):CContext(p_pRes){};

	virtual void Init(void);
	virtual void Activate(void);
	virtual void Deactivate(void);
	virtual void Manage(u32 p_nTimeTick);
	virtual void Update(void);

	void ManageIA(u32 p_nTimeTick);
	void ManageIntro(u32 p_nTimeTick);
	void GameLost(void);
	void OnButtonClick(CEntity* pObj);

	char m_arCorrectAnswer[256];
	char m_arCurrentAnswer[256];

	CSound m_pSndBtn[4];
	CSound m_pSndError;

	u32 m_curStep;
	u32 m_curStepMax;
	u32 m_HighestStep;
	s32 m_delay;
	s32 m_maxDelay;

	bool m_modeAnswer;
	bool m_modeIntro;
};

#endif //CTX_SIMON_H
