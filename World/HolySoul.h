// Copyright (c) 2004 TENGWU Entertainment All rights reserved.
// filename: HolySoul.h
// author: zxzhang
// actor:
// data: 2011-6-8
// last:
// brief: 元神系统
//-----------------------------------------------------------------------------

#ifndef  HOLYSOUL_H
#define  HOLYSOUL_H
class Unit;
class Role;

class HolySoul : public EventMgr<HolySoul>
{
	bool			 m_bSaveToDB; 
	BYTE			 m_bySecondTime;		 //秒计数
	DWORD			 m_dwInitTime;			 	
	tagHolySoulInfo  m_HolySoulInfo;         //元神基本属性
	bool             m_bIsActivated;         //是否已经激活
	volatile EHolySoulState   m_eHolySoulState;       //元神状态
    UINT			 m_nEquipAtt[EHEAT_End]; //装备加成值
    Role*            m_pRole;
public:
     HolySoul(Role* pRole);
	 ~HolySoul();
	 DWORD  Init(void);
	 DWORD  Init(const tagSoulAttProto* pHolySoulInfo);
	 DWORD  Init(const tagHolySoulInfoEx* pHolySoulInfoEx,INT nOffHour/*离线小时*/);

	 VOID   Update();
	 VOID   OnMinute();
	 VOID   OnSecond();


	 //--------------------------------------------------------------------------------------------
	 // 获取元神ID
	 //--------------------------------------------------------------------------------------------
	 DWORD  GetID()const             { return m_HolySoulInfo.SoulAttEx.dwSoulID; }

	 //--------------------------------------------------------------------------------------------
	 // 获得元神伤害属性
	 //--------------------------------------------------------------------------------------------
	 UINT	GetHolySoulAtt(EHolyEquipAttType eEquipAttType)const;

	 //--------------------------------------------------------------------------------------------
	 // 获取元神ID
	 //--------------------------------------------------------------------------------------------
	 EHolySoulState GetState()const	 { return  m_eHolySoulState; }

	 //--------------------------------------------------------------------------------------------
	 // 元神是否觉醒
	 //--------------------------------------------------------------------------------------------
	 bool	IsHolySoulAwake()const 
	 {
	   return ((EHSS_Awake == m_eHolySoulState) ? true : false); 
	 }

	 //--------------------------------------------------------------------------------------------
	 // 获取元神当前经验值
	 //--------------------------------------------------------------------------------------------
	 INT64  GetCurrExp()const        { return m_HolySoulInfo.SoulAttEx.n64LevelExp; }

	 //--------------------------------------------------------------------------------------------
	 // 灌注经验
	 //--------------------------------------------------------------------------------------------
     DWORD  PourExp(INT64 n64ExpLvUp);

	 //--------------------------------------------------------------------------------------------
	 // 获取元神是否激活
	 //--------------------------------------------------------------------------------------------
	 bool   IsActivated()const       { return m_bIsActivated; }

	 //--------------------------------------------------------------------------------------------
	 // 激活元神
	 //--------------------------------------------------------------------------------------------
	 DWORD  ActivateSoul(bool bSend = true);

	 //--------------------------------------------------------------------------------------------
	 // 升级元神
	 //--------------------------------------------------------------------------------------------
	 DWORD  LevelUpSoul();

	 //--------------------------------------------------------------------------------------------
	 // 换上元神装备
	 //--------------------------------------------------------------------------------------------
	 DWORD EquipHolySoul(INT64 n64Serial, DWORD ePosDst);

	 //--------------------------------------------------------------------------------------------
	 // 脱下 -- 目标位置应为空，不空客户端应发换上装备消息
	 //--------------------------------------------------------------------------------------------
	 DWORD UnEquipHolySoul(INT64 n64Serial, INT16 n16IndexDst);

	 //--------------------------------------------------------------------------------------------
	 // 能否穿装备
	 //--------------------------------------------------------------------------------------------
     DWORD	CanEquip(tagEquip* pEquip, DWORD ePosDst);

	 //-------------------------------------------------------------------------------------------
	 // 向客户端广播元神属性
	 //-------------------------------------------------------------------------------------------
	 DWORD SendHolySoulAttToClient();

	 //-------------------------------------------------------------------------------------------
	 // 计算元神属性
	 //-------------------------------------------------------------------------------------------
	 VOID ProcEquipEffect(tagEquip* pNewEquip, tagEquip* pOldEquip, INT16 n16IndexOld, BOOL bDiscard, BOOL bSend);

	 //-------------------------------------------------------------------------------------------
	 // 获取元神基本属性
	 //-------------------------------------------------------------------------------------------
	 tagHolySoulInfo& GetHolySoulInfo() { return m_HolySoulInfo; }

	 //-------------------------------------------------------------------------------------------
	 // 装备计算元神属性
	 //-------------------------------------------------------------------------------------------
	 DWORD  ProcEquipEffectAtt(tagEquip* pEquip, bool bEquip, const INT16 n16Index);

	 //-------------------------------------------------------------------------------------------
	 // 计算元神伤害
	 //-------------------------------------------------------------------------------------------
	 DWORD  CalculateHolySoulDmg(Skill* pSkill,Unit* pSrc, Unit* pTarget);

	 //-------------------------------------------------------------------------------------------
	 // 元神属性修改
	 //-------------------------------------------------------------------------------------------
	 DWORD	OnChangeAttVal(EHolyEquipAttType eEquipAttType,const INT& nVal,bool bSend = true,bool bSaveToDB = true);

	 //--------------------------------------------------------------------------------------------
	 // 累加元神经验，脚本接口
	 //--------------------------------------------------------------------------------------------
	 DWORD  AddExp(INT64 n64ExpValue);

	 //--------------------------------------------------------------------------------------------
	 // 元神加成角色属性
	 //--------------------------------------------------------------------------------------------
	 DWORD  HolyChangeRoleAtt(const tagSoulAttProto* pNewHolySoul = NULL, const tagSoulAttProto* pOldHolySoul = NULL,bool bInit = true,bool bSend = true);

	 //--------------------------------------------------------------------------------------------
	 // 重新计算元神加成角色属性
	 //--------------------------------------------------------------------------------------------
	 DWORD  ReCalHolyChangeRoleAtt(const tagSoulAttProto* pNewHolySoul,bool bSend = true);

	 //元神转生
	 DWORD  HolySoulReborn();

	 //--------------------------------------------------------------------------------------------
	 // 元神降级
	 //--------------------------------------------------------------------------------------------
	 DWORD  LevelDownSoul(BYTE byLevel);

	 //-------------------------------------------------------------------------------------------
	 // 重新加载计算元神属性
	 //-------------------------------------------------------------------------------------------
	 DWORD ReloadProcHolySoulAtt(const tagSoulAttProto* pNewHolySoul );
private:
	//-------------------------------------------------------------------------------------------
	// 冲星强化属性加成
	//-------------------------------------------------------------------------------------------
	DWORD ProcStarEnhanceAtt(const tagStarEnhanceProto* pStarEnhanceProto,INT nFactor,EHolyEquipAttType eHolyEquipPosAtt);

	//-------------------------------------------------------------------------------------------
	// 装备镶嵌加成
	//-------------------------------------------------------------------------------------------
	DWORD ProcHolySoulEquipInlay(tagEquip* pEquip, INT nFactor);

	//-------------------------------------------------------------------------------------------
	// 元神装备镶嵌助力加成
	//-------------------------------------------------------------------------------------------
	DWORD ProcHolySoulEquipInlayEx(tagEquip* pEquip, INT nFactor);

	//--------------------------------------------------------------------------------------------
	//计算元神装备淬炼加成
	//--------------------------------------------------------------------------------------------
	DWORD ProcHolySoulEquipConsolidate(tagEquip* pEquip,INT nFactor);

	//-------------------------------------------------------------------------------------------
	// 升级计算元神属性
	//-------------------------------------------------------------------------------------------
	 DWORD ProcHolySoulAtt(const tagSoulAttProto* pNewHolySoul, const tagSoulAttProto* pOldHolySoul, bool bSend = false);


	 //-------------------------------------------------------------------------------------------
	 // 元神元神经验改变
	 //-------------------------------------------------------------------------------------------
     DWORD	ExpChange(INT64& n64ExpMod, bool& bSend);	

	 //-------------------------------------------------------------------------------------------
	 // 设置元神元神状态
	 //-------------------------------------------------------------------------------------------
	 VOID  SetState(DWORD dwSenderID, LPVOID pEventMessage);

	 //-------------------------------------------------------------------------------------------
	 // 元神元神值恢复
	 //-------------------------------------------------------------------------------------------
	 VOID  OnChangeSoulVal(const INT& nVal,bool bSend = true);

	 //-------------------------------------------------------------------------------------------
	 // 召唤元神
	 //-------------------------------------------------------------------------------------------
	 VOID  CallHolySoul(EHolySoulState eHolySoulState);

	 //-------------------------------------------------------------------------------------------
	 // 取消召唤元神
	 //-------------------------------------------------------------------------------------------
	 VOID  CancelCallSoul(EHolySoulState eHolySoulState);

public:
	enum SaveType
	{
		ESaveType_Insert        = 1 ,
		ESaveType_Update        = 2 ,
		ESaveType_SystemUpdate  = 3 ,
		ESaveType_ExpAttUpdate	= 4 ,
		ESaveType_AttInfoUpdate = 5 ,
	};

	//-------------------------------------------------------------------------------------------
	// 插入元神属性
	//-------------------------------------------------------------------------------------------
	DWORD SaveHolySoulInfoToDB(SaveType eSaveType,OUT LPVOID pOutPointer = NULL,ESoulAttTypeEx eSoulAttTypeEx = ESoulAttEx_Null,DWORD dwVal = 0);
public:
	//----------------------------------------------------------------------------
	// 计算格挡
	//----------------------------------------------------------------------------
	bool  CalculateBlock();

	//--------------------------------------------------------------------------------
	// 计算命中
	//--------------------------------------------------------------------------------
	bool	CalculateHit(Skill* pSkill,Unit* pSrc, Unit* pTarget);

	//-----------------------------------------------------------------------------
	// 计算攻击伤害
	//-----------------------------------------------------------------------------
	float  CalculateDmg(Skill* pSkill,Unit* pSrc, Unit* pTarget);

	//------------------------------------------------------------------------------
	// 计算基础伤害
	//------------------------------------------------------------------------------
	float CalBaseDmg(Skill* pSkill,Unit* pSrc);

	//-----------------------------------------------------------------------------
	// 计算攻防影响
	//-----------------------------------------------------------------------------
	float CalAttackDefenceCoef(Skill* pSkill,Unit* pSrc ,Unit* pTarget);

	//-------------------------------------------------------------------------
	// 计算等级影响
	//-------------------------------------------------------------------------
	float CalLevelCoef(Skill* pSkill, Unit* pSrc ,Unit* pTarget);

	//-----------------------------------------------------------------------
	// 计算士气影响
	//-----------------------------------------------------------------------
	float CalMoraleCoef(Unit* pSrc ,Unit* pTarget);

	//------------------------------------------------------------------------
	// 计算减免影响
	//------------------------------------------------------------------------
	float CalDerateCoef(Skill* pSkill,Unit* pSrc,Unit* pTarget);

	//------------------------------------------------------------------------
	// 计算内伤影响
	//------------------------------------------------------------------------
	float CalInjuryCoef(Unit* pSrc);

	//------------------------------------------------------------------------
	// 计算韧性影响
	//------------------------------------------------------------------------
	float CalToughnessCoef(Unit* pSrc ,Unit* pTarget);

	//------------------------------------------------------------------------
	// 计算默契影响
	//------------------------------------------------------------------------
	float CalCovalueCoef();

	//------------------------------------------------------------------------
	// 计算致命率
	//------------------------------------------------------------------------
	bool CalculateCrit(Skill* pSkill,Unit* pSrc, Unit* pTarget);

	//------------------------------------------------------------------------
	// 计算致命量
	//------------------------------------------------------------------------
	float CalculateCritAmount(Unit* pSrc);
private:
	HolySoul(const HolySoul&);
    HolySoul& operator=(const HolySoul&);
};


//----------------------------------------------------------------------------
// 计算格挡
//----------------------------------------------------------------------------
inline bool HolySoul::CalculateBlock()
{
     return  false;
}

//--------------------------------------------------------------------------------
// 计算命中
//--------------------------------------------------------------------------------
inline bool HolySoul::CalculateHit(Skill* pSkill,Unit* pSrc, Unit* pTarget)
{

	if ( !pSrc->IsRole())
	{
		return 0.0f;
	}
	//元神攻击命中率 = 1×[1-（防御方灵敏-攻击方精准）/10000-（防御方当前闪避-攻击方当前命中）/10000]+技能命中率
	//其中，1×[1-（防御方当前闪避-攻击方当前命中）/10000]的取值范围为30%~100%

	
	float fHitTemp = 1 - ((FLOAT)(pTarget->GetAttValue(ERA_Dodge)) - (FLOAT)(GetHolySoulAtt(EHEAT_Hit))) / 10000.0f;
	// 范围：30——100%
	if( fHitTemp < 0.3f ) fHitTemp = 0.3f;
	if( fHitTemp > 1.0f ) fHitTemp = 1.0f;

	float fSoulHit = 1*(fHitTemp - ((FLOAT)(pTarget->GetAttValue(ERA_AttackTec) - (FLOAT)(GetHolySoulAtt(EHEAT_Accurate))))/ 10000.0f) + pSkill->GetHit();

	// 范围：30——100%
	if( fSoulHit < 0.3f ) fSoulHit = 0.3f;
	if( fSoulHit > 1.0f ) fSoulHit = 1.0f;

	// 随机看是否能命中
	return (((IUTIL->Probability(INT(fSoulHit*100.0f)))== FALSE) ? false : true);

}

//-----------------------------------------------------------------------------
// 计算攻击伤害
//-----------------------------------------------------------------------------
inline float  HolySoul::CalculateDmg(Skill* pSkill,Unit* pSrc, Unit* pTarget)
{
	//元神攻击伤害 = 基础伤害×攻防影响×等级影响×士气影响×减免影响×内伤影响×韧性影响×默契值影响 +（额外伤害 – 额外伤害减免）×韧性影响×默契值影响×动作时间÷技能攻击次数
	float fBaseDmg				 = CalBaseDmg(pSkill,pSrc);
	float fDefenceCoef			 = CalAttackDefenceCoef(pSkill,pSrc,pTarget);
	float fLevelCoef			 = CalLevelCoef(pSkill,pSrc,pTarget);
	float fMoraleCoef			 = CalMoraleCoef(pSrc,pTarget);
	float fDerateCoef			 = CalDerateCoef(pSkill,pSrc,pTarget);
	float fInjuryCoef			 = CalInjuryCoef(pSrc);
	float fToughnessCoef		 = CalToughnessCoef(pSrc,pTarget);
	float fCovalueCoef			 = CalCovalueCoef();
	float fExDemage				 = (float)GetHolySoulAtt(EHEAT_Exdamage);
	float fExDemageCoef			 = (float)pTarget->GetAttValue(ERA_ExDamage_Absorb);


	float fExDemageVal =  fExDemage - fExDemageCoef;
	if ( fExDemageVal <= 0)
	{
		fExDemageVal = 0;
	}


	float fActionTime(0.0);
	fActionTime = (float)pSkill->GetActionTime() + (float)pSkill->GetPrepareTime() / 1000.0f;
	if( fActionTime > 4 )
		fActionTime = 4;

	INT nDmgTimes = pSkill->GetDmgTimes();
	if( nDmgTimes <= 0 )
		nDmgTimes = 1;

	float fDmg =  fBaseDmg*fDefenceCoef*fLevelCoef*fMoraleCoef*fDerateCoef*fInjuryCoef*fToughnessCoef*fCovalueCoef+ 
		         (fExDemageVal)*fToughnessCoef*fCovalueCoef*fActionTime/(float)nDmgTimes;
	return fDmg;
}

//------------------------------------------------------------------------------
// 计算基础伤害
//------------------------------------------------------------------------------
inline float HolySoul::CalBaseDmg(Skill* pSkill,Unit* pSrc)
{
	
	// 基础伤害=(绝技伤害+技能威力) ×动作时间/技能攻击次数×（1+（攻击方当前外功攻击+攻击方当前内功攻击）/20000）+（攻击方当前外功攻击+攻击方当前内功攻击）×0.01×动作时间/技能攻击次数

	float fWeaponDmg =	(float)(IUTIL->RandomInRange(pSrc->GetAttValue(ERA_WeaponDmgMin), pSrc->GetAttValue(ERA_WeaponDmgMax)))/(float)pSkill->GetDmgTimes();

	float fBaseHit = ((float)(GetHolySoulAtt(EHEAT_Demage) + fWeaponDmg) * pSkill->GetActionTime() / (float)pSkill->GetDmgTimes() )*(1+(GetHolySoulAtt(EHEAT_Exattack)+GetHolySoulAtt(EHEAT_InExattack))/20000.0f)+
		(GetHolySoulAtt(EHEAT_Exattack) + GetHolySoulAtt(EHEAT_InExattack))*0.01f * pSkill->GetActionTime() / (float)pSkill->GetDmgTimes();
	return fBaseHit;
}

//-----------------------------------------------------------------------------
// 计算攻防影响
//-----------------------------------------------------------------------------
inline float HolySoul::CalAttackDefenceCoef(Skill* pSkill,Unit* pSrc ,Unit* pTarget)
{
// 	if ( !pSrc->IsRole())
// 	{
// 		return 0.0f;
// 	}
// 
// 	//攻防影响= [1+（（攻击方外功攻击+攻击方内功攻击）-（防御方外防御+防御方内防御））/（1000+攻方等级*22）]*（1-防御方防御技巧/（10000+攻方等级*220）
// 	//50%<=[1+（（攻击方外功攻击+攻击方内功攻击）-（防御方外外防御+防御方内功防御））/（1000+攻方等级*22）]<=200%
// 	//50%<=（1-防御方防御技巧/（10000+攻方等级*220）<=200%
// 
// 
// 	float fDefCoef = 1.0f + (float)( ((INT)GetHolySoulAtt(EHEAT_Exattack) + (INT)GetHolySoulAtt(EHEAT_InExattack)) - pTarget->GetAttValue(ERA_ExDefense) - pTarget->GetAttValue(ERA_InDefense)) / (float)( 1000 + m_HolySoulInfo.SoulAtt.nSoulAtt[ESAT_SoulLevel]*22);
// 	
// 	// 范围：50——200%
// 	if( fDefCoef < 0.5f ) fDefCoef = 0.5f;
// 	if( fDefCoef > 2.0f ) fDefCoef = 2.0f;
// 
// 	//（1-防御方防御技巧/（10000+攻方等级*220）
// 	float fDelCoefSkill = 0.0f;
// 	fDelCoefSkill = 1.0f - (float)pTarget->GetAttValue(ERA_DefenseTec) / ( 10000 + m_HolySoulInfo.SoulAtt.nSoulAtt[ESAT_SoulLevel]*220);
// 	// 范围：50——200%
// 	if (fDelCoefSkill < 0.5f)
// 	{
// 		fDelCoefSkill = 0.5f;
// 	}
// 	if (fDelCoefSkill > 2.0f)
// 	{
// 		fDelCoefSkill = 2.0f;
// 	}
// 
// 	fDefCoef = fDefCoef*fDelCoefSkill;
// 	return fDefCoef;
	return 0;
}

//-------------------------------------------------------------------------
// 计算等级影响
//-------------------------------------------------------------------------
inline float HolySoul::CalLevelCoef(Skill* pSkill, Unit* pSrc ,Unit* pTarget)
{
// 	if ( !pSrc->IsRole())
// 	{
// 		return 0.0f;
// 	}
// 	//等级影响=1-（防御方等级-攻击方等级）/75     取值（0.5~1.5）
// 
// 	float fLvCoef = 1.0f - (float)((float)pTarget->GetLevel() - (float)m_HolySoulInfo.SoulAtt.nSoulAtt[ESAT_SoulLevel]) / 75.0f;
// 
// 	// 范围：0.5~1.5
// 	if( fLvCoef < 0.5f ) fLvCoef = 0.5f;
// 	if( fLvCoef > 1.5f ) fLvCoef = 1.5f;
// 
// 	return fLvCoef;
	return 0;
}

//------------------------------------------------------------------------
// 计算减免影响
//------------------------------------------------------------------------
inline float HolySoul::CalDerateCoef(Skill* pSkill,Unit* pSrc,Unit* pTarget)
{
// 	float fDerateCoef = 1.0f;
// 	if ( !pSrc->IsRole() )
// 	{
// 		return fDerateCoef;
// 	}
// 
// 	ERoleAttribute eAtt = pTarget->SkillDmgType2ERA(ESDGT_Stunt);
// 	if( ERA_Null == eAtt ) 
// 	{
// 		return fDerateCoef;
// 	}
// 	float fDmgDeepen = 0;
// 	fDmgDeepen = (float)pSrc->GetAttValue(pSrc->SkillDeepenDmgType2ERA(ESDGT_Stunt));
// 
// 	//减免影响=1-防御方伤害减免			
// 	//防御方绝技伤害减免 = （绝技伤害减免 + 全部伤害减免 – 人物等级）/ 1000	
// 	float fTargetCoef =(float)(pTarget->GetAttValue(eAtt) - fDmgDeepen +(float)pTarget->GetAttValue(ERA_Derate_ALL) - (float)pTarget->GetLevel()) / 1000.0f;
// 	fDerateCoef = 1.0f - 	fTargetCoef;
// 
// 	if( fDerateCoef < 0.2f ) fDerateCoef = 0.2f;
// 	if( fDerateCoef > 2.0f ) fDerateCoef = 2.0f;
// 
// 	return fDerateCoef;
	return 0;
}

//------------------------------------------------------------------------
// 计算内伤影响
//------------------------------------------------------------------------
inline float HolySoul::CalInjuryCoef(Unit* pSrc)
{
	//内伤影响=1－内伤×0.1÷（4＋内伤×0.06）
// 	float fInjuryCoef = (1.0f -(float)pSrc->GetAttValue(ERA_Injury) * 0.1f / (4.0f + (float)pSrc->GetAttValue(ERA_Injury) * 0.06f));
// 	return fInjuryCoef;
	return 0;
}

//------------------------------------------------------------------------
// 计算韧性影响
//------------------------------------------------------------------------
inline float HolySoul::CalToughnessCoef(Unit* pSrc ,Unit* pTarget)
{
	// 韧性影响：
	// 若攻击方为怪物：韧性影响=1
	// 韧性效果 = 防御方韧性 – 攻击方忽视韧性 （韧性效果 取值范围：0~99999，小于0取0）
	// 若攻击方为玩家：韧性影响 = 1-韧性效果/10000
// 	float fToughness = (float)pTarget->GetAttValue(ERA_Toughness) - GetHolySoulAtt(EHEAT_Toughness);
// 
// 	if( fToughness < 0.0f ) fToughness = 0.0f;
// 	if( fToughness > 9999.0f ) fToughness = 99999.0f;
// 
// 	float fToughnessCoef = 1.0f - fToughness / 10000.0f;
// 
// 	return fToughnessCoef;
	return 0;
}

//------------------------------------------------------------------------
// 计算默契影响
//------------------------------------------------------------------------
inline float HolySoul::CalCovalueCoef()
{
	// 默契值影响 = 默契值/100			取值（0.5 ~ 1）
// 	float fCovalueCoef = (float)GetHolySoulAtt(EHEAT_Covalue) / 100.0f;
// 	
// 	if( fCovalueCoef < 0.5f ) fCovalueCoef = 0.5f;
// 	if( fCovalueCoef > 1.0f ) fCovalueCoef = 1.0f;
// 
// 	return fCovalueCoef;
	return 0;
}

//------------------------------------------------------------------------
// 计算致命率
//------------------------------------------------------------------------
inline bool HolySoul::CalculateCrit(Skill* pSkill,Unit* pSrc, Unit* pTarget)
{
	// 元神攻击致命率 = 基础致命率×(攻击方当前攻击技巧/被攻击方当前防御技巧)^0.5+致命加成/1000+技能附带致命率
	//【基础致命率=（攻击方当前攻击技巧/200000）^0.5】
// 	float fCrit = 0.0f;
// 	fCrit = pSrc->GetAttValue(ERA_AttackTec) / 200000.0f;
// 	fCrit = IFASTCODE->FastSqrt(fCrit * ((FLOAT)pSrc->GetAttValue(ERA_AttackTec) / (FLOAT)pTarget->GetAttValue(ERA_DefenseTec))) + 
// 		GetHolySoulAtt(EHEAT_Crit) / 1000.0f + pSkill->GetCrit();
// 	if (fCrit < 0.0f)
// 	{
// 		fCrit = 0.0f;
// 	}
// 	if (fCrit > 1.0f)
// 	{
// 		fCrit = 1.0f;
// 	}

	// 随机看是否能命中
	//return (bool)IUTIL->Probability(INT(fCrit*100.0f));
	return 0;
}

//------------------------------------------------------------------------
// 计算致命量
//------------------------------------------------------------------------
inline float HolySoul::CalculateCritAmount(Unit* pSrc)
{
	//【致命伤害量加成=（（攻击方元神内功攻击+攻击方元神外功攻击）/8000）^0.25+攻击方元神致命量/10000】
// 	float fCritAmount = 0.0f;
// 	fCritAmount = pow((GetHolySoulAtt(EHEAT_InExattack) + GetHolySoulAtt(EHEAT_Exattack)) / 8000.0f, 0.25f) + GetHolySoulAtt(EHEAT_CritAmount) / 10000.0f;	
// 
// 	return fCritAmount;
	return 0;
}
#endif