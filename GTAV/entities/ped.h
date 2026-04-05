#pragma once
#include "entity.h"
#include <ModCore/rage/HashString.h>
struct sBlendDataRaw {
	public: int shapeFirst, shapeSecond; private: int pad;
	public: int skinFirst, skinSecond;  private: int pad1;
	public: float shapeMix, skinMix; private: float pad2;
};
enum eFaceFeature {
	EFF_NoseWidth,
	EFF_NosePeak,
	EFF_NoseLength,
	EFF_NoseBoneCurveness,
	EFF_NoseTip,
	EFF_NoseBoneTwist,
	EFF_EyebrowVertical,
	EFF_EyebrowHoriztonal,
	EFF_CheekBoneVertical,
	EFF_CheekBoneInOrOut,
	EFF_CheekBoneWidth,
	EFF_EyeOpening,
	EFF_LipThickness,
	EFF_JawBoneWidth,
	EFF_JawBoneShape,
	EFF_ChinBoneVertical,
	EFF_ChinBoneLength,
	EFF_ChinBoneShape,
	EFF_ChinHole,
	EFF_NeckThickness,
};
enum eEyeColor {
	Black,
	VeryLightBlueGreen,
	DarkBlue,
	Brown,
	DarkerBrown,
	LightBrown,
	Blue,
	LightBlue,
	Pink,
	Yellow,
	Purple,
	DarkGreen,
	YellowBlackPattern,
	LightColoredSpiralPattern,
	ShinyRed,
	ShinyHalfBlueHalfRed,
	HalfBlackHalfLightBlue,
	WhiteRedPerimeter,
	GreenSnake,
	RedSnake,
	DarkBlueSnake,
	DarkYellow,
	BrightYellow,
	AllBlack,
	RedSmallPupil,
	DevilBlueBlack,
	WhiteSmallPupil,
	GlossedOver
};
enum ePedVarComp {
	PV_COMP_INVALID = 0xFFFFFFFF,
	PV_COMP_HEAD = 0, // "HEAD"
	PV_COMP_BERD = 1, // "BEARD"
	PV_COMP_HAIR = 2, // "HAIR"
	PV_COMP_UPPR = 3, // "UPPER"
	PV_COMP_LOWR = 4, // "LOWER"
	PV_COMP_HAND = 5, // "HAND"
	PV_COMP_FEET = 6, // "FEET"
	PV_COMP_TEEF = 7, // "TEETH"
	PV_COMP_ACCS = 8, // "ACCESSORIES"
	PV_COMP_TASK = 9, // "TASK"
	PV_COMP_DECL = 10, // "DECL"
	PV_COMP_JBIB = 11, // "JBIB"
	PV_COMP_MAX = 12,
};
class CPed : public CEntity {
private:
public:
	CPed(Ped& PedHandle) : CEntity(PedHandle) {
		PedHandle = 0;
	}
	CPed() = default;
	CPed(int iType, rage::HashString Hash, legit::Vec3f Position, float fHeading, bool IsNet, bool IsScriptHostPed) : CEntity(PED::CREATE_PED(iType, Hash.ToHash(), legit::Promote(Position), fHeading, IsNet, IsScriptHostPed)) {}
	void SetAsNoLongerNeeded() const override {
		int iHandle = this->GetHandle();
		ENTITY::SET_PED_AS_NO_LONGER_NEEDED(iHandle);
	}
	void SetHeadBlendData(const sBlendDataRaw& raw, bool bIsParent) {
		PED::SET_PED_HEAD_BLEND_DATA(this->GetHandle(), raw.shapeFirst, raw.shapeSecond, 0, raw.skinFirst, raw.skinSecond, 0, raw.shapeMix, raw.skinMix, 0, bIsParent);
	}
	void SetHairTint(int iColor, int iHighlight) {
		PED::SET_PED_HAIR_TINT(this->GetHandle(), iColor, iHighlight);
	}
	void SetFaceFeature(eFaceFeature Feature, float fValue) {
		rage::Clamp(fValue, -1.f, 1.f);
		PED::SET_PED_MICRO_MORPH(this->GetHandle(), Feature, fValue);
	}
	void SetEyeColor(eEyeColor Color) {
		PED::SET_HEAD_BLEND_EYE_COLOR(this->GetHandle(), Color);
	}
	int GetNumberOfDrawableVariations(ePedVarComp iComponent) {
		return PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(this->GetHandle(), iComponent);
	}
	int GetNumberOfTextureVariations(ePedVarComp iComponent, int iDrawableId) {
		return PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(this->GetHandle(), iComponent, iDrawableId);
	}
	bool IsModel(rage::HashString String) {
		return PED::IS_PED_MODEL(this->GetHandle(), String.ToHash());
	}
	bool SetPedToRagdollRelax(int iMinTime, int iMaxTime, bool bAbortIfInjured, bool bAbortIfDead, bool bForceScriptControl) {
		return PED::SET_PED_TO_RAGDOLL(this->GetHandle(), iMinTime, iMaxTime, 0, bAbortIfInjured, bAbortIfDead, bForceScriptControl);
	}
	bool SetPedToRagdollScriptControl(bool bAbortIfInjured, bool bAbortIfDead, bool bForceScriptControl) {
		return PED::SET_PED_TO_RAGDOLL(this->GetHandle(), 0, 1, 1, bAbortIfInjured, bAbortIfDead, bForceScriptControl);
	}
	void Resurrect() {
		PED::RESURRECT_PED(this->GetHandle());
	}
	bool IsStopped() {
		return PED::IS_PED_STOPPED(this->GetHandle());
	}
	bool IsRagdolling() {
		return PED::IS_PED_RAGDOLL(this->GetHandle());
	}
	bool CanRagdoll() {
		return PED::CAN_PED_RAGDOLL(this->GetHandle());
	}
	void DisableRagdoll() {
		PED::SET_PED_CAN_RAGDOLL(this->GetHandle(), false);
	}
	void EnableRagdoll() {
		PED::SET_PED_CAN_RAGDOLL(this->GetHandle(), true);
	}
	void CancelTask() {
		TASK::CLEAR_PED_TASKS(this->GetHandle());
	}
	void CancelAllTasksImmediately() {
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(this->GetHandle());
	}
	bool IsFleeing() {
		return PED::IS_PED_FLEEING(this->GetHandle());
	}
	void SetPedFlag(int iFlag, bool bValue) {
		PED::SET_PED_CONFIG_FLAG(this->GetHandle(), iFlag, bValue);
	}
	void SetPedComponent(int iComponent, int iDrawable, int iTexture, int iPalette) {
		PED::SET_PED_COMPONENT_VARIATION(this->GetHandle(), iComponent, iDrawable, iTexture, iPalette);
	}
	void BlockPermanentEvents() {
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(this->GetHandle(), true);
	}
	void UnblockPermanentEvents() {
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(this->GetHandle(), false);
	}
	void SetFleeAttributes(int iFlag, bool bValue) {
		PED::SET_PED_FLEE_ATTRIBUTES(this->GetHandle(), iFlag, bValue);
	}
	void SetPedCombatAttributes(int iFlag, bool bValue) {
		PED::SET_PED_COMBAT_ATTRIBUTES(this->GetHandle(), iFlag, bValue);
	}
	CPed& operator=(CPed&&) = default;
	CPed(CPed&&) = default;
protected:

private:
	// Inherited via CEntity
	void DeleteInternal() override {
		int iHandle = this->GetHandle();
		PED::DELETE_PED(iHandle);
	}

};
