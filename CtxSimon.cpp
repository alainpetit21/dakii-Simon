#include "lib.h"
#include "libTypes.h"
#include "libMngInput.h"
#include "dfcApp.h"
#include "CtxSimon.h"

void
CCtxSimon::Init(void)
{
	SetNbChilds(32);
}

void
CCtxSimon::Activate(void)
{
	CContext::Activate();

	for(int i= 0; i < 256; ++i)
		m_arCorrectAnswer[i]= 1 + (rand() % 4);

	m_modeIntro	= 1;
	m_modeAnswer= 0;
	m_curStep	= 0;
	m_curStepMax= 1;
	m_HighestStep= m_curStepMax;
	m_maxDelay	= 1000;
	m_delay		= m_maxDelay;
	memset(m_arCurrentAnswer, 0, sizeof(char)*256);

	m_pSndBtn[0].LoadInstance("BtAngle000.sound");
	m_pSndBtn[1].LoadInstance("BtAngle064.sound");
	m_pSndBtn[2].LoadInstance("BtAngle128.sound");
	m_pSndBtn[3].LoadInstance("BtAngle192.sound");
	m_pSndError.LoadInstance("Error.sound");

	AddMap(CEntity::mapMouseClick, "BtAngle000", (TCallback)&CCtxSimon::OnButtonClick);
	AddMap(CEntity::mapMouseClick, "BtAngle064", (TCallback)&CCtxSimon::OnButtonClick);
	AddMap(CEntity::mapMouseClick, "BtAngle128", (TCallback)&CCtxSimon::OnButtonClick);
	AddMap(CEntity::mapMouseClick, "BtAngle192", (TCallback)&CCtxSimon::OnButtonClick);

#ifdef _GP2X
	((CPhysObj*)FindByID("BackSimon_1"))->SetPosX(320);
	((CPhysObj*)FindByID("BackSimon_1"))->MoveToFreely(160, 120, 100, float(1.0), float(10.0), float(0.8), float(0.8));
#elif defined(_LINUX)
	((CPhysObj*)FindByID("BackSimon_1"))->SetPosX(640);
	((CPhysObj*)FindByID("BackSimon_1"))->MoveToFreely(320, 240, 100, float(1.0), float(20.0), float(0.9), float(0.9));
#endif
}

void
CCtxSimon::Deactivate(void)
{
	CContext::Deactivate();

}

void
CCtxSimon::ManageIntro(u32 p_nTimeTick)
{
#ifdef _GP2X
	if(((CPhysObj*)FindByID("BackSimon_1"))->GetPosX() == 160){
#elif defined(_LINUX)
	if(((CPhysObj*)FindByID("BackSimon_1"))->GetPosX() == 320){
#endif
		m_modeIntro= 0;
	}

	CContext::Manage(p_nTimeTick);
}

void
CCtxSimon::ManageIA(u32 p_nTimeTick)
{
	SetMouse(0);
	m_delay-= p_nTimeTick;

	if(m_delay < 0){
		m_delay= m_maxDelay;
		m_pSndBtn[int(m_arCorrectAnswer[m_curStep])-1].Play();

		switch(m_arCorrectAnswer[m_curStep++] - 1){
			case 0:	Click((CButton*)FindByID("BtAngle000"));	break;
			case 1:	Click((CButton*)FindByID("BtAngle064"));	break;
			case 2:	Click((CButton*)FindByID("BtAngle128"));	break;
			case 3:	Click((CButton*)FindByID("BtAngle192"));	break;
			default:	break;
		}

		if(m_curStep == m_curStepMax){
			m_curStep	= 0;
			m_modeAnswer= true;
		}
	}

	CContext::Manage(p_nTimeTick);
}

void
CCtxSimon::Manage(u32 p_nTimeTick)
{
CMngInput *mngInput= GetMngInput();

	if(m_modeIntro){
		ManageIntro(p_nTimeTick);
		return;
	}
	if(!m_modeAnswer){
		ManageIA(p_nTimeTick);
		return;
	}

	if(mngInput->IsLogicKeyDown(IK_BTN_B) || mngInput->IsLogicKeyDown(IK_RIGHT)){
		Click((CButton*)FindByID("BtAngle000"));
	}else if(mngInput->IsLogicKeyDown(IK_BTN_X) || mngInput->IsLogicKeyDown(IK_DOWN)){
		Click((CButton*)FindByID("BtAngle064"));
	}else if(mngInput->IsLogicKeyDown(IK_BTN_A) || mngInput->IsLogicKeyDown(IK_LEFT)){
		Click((CButton*)FindByID("BtAngle128"));
	}else if(mngInput->IsLogicKeyDown(IK_BTN_Y) || mngInput->IsLogicKeyDown(IK_UP)){
		Click((CButton*)FindByID("BtAngle192"));
	}else if(mngInput->IsLogicKeyDown(IK_BTN_START)){
		System_Quit();
	}else if(mngInput->IsLogicKeyDown(IK_BTN_SELECT)){
		GameLost();
	}

	CContext::Manage(p_nTimeTick);
}

void
CCtxSimon::Update(void)
{

	CContext::Update();
}

void
CCtxSimon::GameLost(void)
{
	if(m_curStepMax > m_HighestStep)
		m_HighestStep= m_curStepMax;

	m_curStep	= 0;
	m_modeAnswer= false;
	m_curStepMax= 1;

	for(int i= 0; i < 256; ++i)
		m_arCorrectAnswer[i]= 1 + (rand() % 4);

	((CLabel*)FindByID("LblScore"))->SetText(m_curStepMax-1);
	((CLabel*)FindByID("LblSpeed"))->SetText(1000 - (m_maxDelay= 1000));
	((CLabel*)FindByID("LblHighest"))->SetText(m_HighestStep-1);
}
void
CCtxSimon::OnButtonClick(CEntity* pObj)
{
	if(!m_modeAnswer)
		return;

	if(strcmp(pObj->m_stringID, "BtAngle000") == 0)
		m_arCurrentAnswer[m_curStep]= 1;
	else if(strcmp(pObj->m_stringID, "BtAngle064") == 0)
		m_arCurrentAnswer[m_curStep]= 2;
	else if(strcmp(pObj->m_stringID, "BtAngle128") == 0)
		m_arCurrentAnswer[m_curStep]= 3;
	else if(strcmp(pObj->m_stringID, "BtAngle192") == 0)
		m_arCurrentAnswer[m_curStep]= 4;


	//Verification
	if(strncmp(m_arCorrectAnswer, m_arCurrentAnswer, (m_curStep+1)) != 0){
		GameLost();
		m_pSndError.Play();
		return;
	}else{
		m_pSndBtn[m_arCurrentAnswer[m_curStep]-1].Play();
	}

	++m_curStep;
	if(m_curStep == m_curStepMax){
		m_curStep	= 0;
		m_modeAnswer= false;
		++m_curStepMax;

		if(m_curStepMax == 256)
			m_curStepMax= 255;

		m_maxDelay-= 50;

		if(m_maxDelay < 250)
			m_maxDelay = 250;

		((CLabel*)FindByID("LblScore"))->SetText(m_curStepMax-1);
		((CLabel*)FindByID("LblSpeed"))->SetText(1000 - m_maxDelay);
	}
}
