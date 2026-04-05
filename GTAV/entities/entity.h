#pragma once
#include <GTAV/resourcehandler.h>
#include <ModCore/math/Vector3.h>
#include <ModCore/thirdparty/ScriptHook/include/natives.h>
#include <ModCore/rage/numbers.h>
class CEntity : public gtaResourceHandler {
public:
	CEntity() = default;
	explicit CEntity(Entity& Handle) : gtaResourceHandler(Handle) {}
	CEntity(CEntity&&) = default;
	CEntity& operator=(CEntity&&) = default;
protected:
	CEntity(const Entity& Handle) : gtaResourceHandler(Handle) { // Specifically to resource creation.

	};
public:
	legit::Vec3f GetForwardVector() {
		return legit::Demote(ENTITY::GET_ENTITY_FORWARD_VECTOR(this->GetHandle()));
	}
	void SetAlpha(float fAlpha, bool bAffectSkin) {
		rage::Clamp(fAlpha, 0.f, 1.f);
		ENTITY::SET_ENTITY_ALPHA(this->GetHandle(), fAlpha * 255l, bAffectSkin);
	}
	void ResetAlpha() {
		ENTITY::RESET_ENTITY_ALPHA(this->GetHandle());
	}
	void SetPosition(legit::Vec3f Pos, bool bAlive, bool bDeadFlag, bool bRagDollFlag, bool bClearArea) {
		ENTITY::SET_ENTITY_COORDS(this->GetHandle(), legit::Promote(Pos), bAlive, bDeadFlag, bRagDollFlag, bClearArea);
	}
	legit::Vec3f GetPosition(bool bAlive) {
		return legit::Demote(ENTITY::GET_ENTITY_COORDS(this->GetHandle(), bAlive));
	}
	float GetHeading() {
		return ENTITY::GET_ENTITY_HEADING(this->GetHandle());
	}
	void SetHeading(float fHead) {
		ENTITY::SET_ENTITY_HEADING(this->GetHandle(), fHead);
	}
	bool IsAnEntity() const {
		return ENTITY::IS_AN_ENTITY(this->GetHandle());
	}
	bool IsAMissionEntity() const {
		return ENTITY::IS_ENTITY_A_MISSION_ENTITY(this->GetHandle());
	}
	bool IsAPed() const {
		return ENTITY::IS_ENTITY_A_PED(this->GetHandle());
	}
	bool IsAnObject() const {
		return ENTITY::IS_ENTITY_AN_OBJECT(this->GetHandle());
	}
	bool IsAVehicle() const {
		return ENTITY::IS_ENTITY_A_VEHICLE(this->GetHandle());
	}
	bool IsDead(bool bUnk) const {
		return ENTITY::IS_ENTITY_DEAD(this->GetHandle(), bUnk);
	}
	bool DoesExist() const {
		return ENTITY::DOES_ENTITY_EXIST(this->GetHandle());
	}
	// Verbs. Makes it clearer on intention.
	void Freeze() const {
		ENTITY::FREEZE_ENTITY_POSITION(this->GetHandle(), true);
	}
	void Unfreeze() const {
		ENTITY::FREEZE_ENTITY_POSITION(this->GetHandle(), false);
	}
	void SetLODDistance(int iDistance) const {
		ENTITY::SET_ENTITY_LOD_DIST(this->GetHandle(), iDistance);
	}
	virtual void SetAsNoLongerNeeded() const {
		int _newHandle = GetHandle();
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(_newHandle);
	}
	void EnableCollision(bool bKeepPhysics) {
		ENTITY::SET_ENTITY_COLLISION(this->GetHandle(), true, bKeepPhysics);
	}
	void DisableCollision(bool bKeepPhysics) {
		ENTITY::SET_ENTITY_COLLISION(this->GetHandle(), false, bKeepPhysics);
	}
	virtual ~CEntity() = default;
protected:
	virtual void DeleteInternal() {
		int _newHandle = (this->GetHandle());
		ENTITY::DELETE_ENTITY(_newHandle);
	}
private:

};
