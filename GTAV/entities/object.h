#pragma once
#include "entity.h"
class CObject : public CEntity {
public:
	CObject() = default;
	CObject(const rage::HashString& mHash, legit::Vec3f Position, bool IsNet, bool isScriptHostObj, bool isDynamic) : CEntity(OBJECT::CREATE_OBJECT(mHash.ToHash(), legit::Promote(Position), IsNet, isScriptHostObj, isDynamic)) {}
	CObject(CObject&&) = default;
	CObject& operator=(CObject&&) = default;
	~CObject() {}
	void SetAsNoLongerNeeded() const {
		int _newHandle = this->GetHandle();
		ENTITY::SET_OBJECT_AS_NO_LONGER_NEEDED(_newHandle); // useless.
	}
protected:
	void DeleteInternal() override {
		int iHandle = (this->GetHandle());
		OBJECT::DELETE_OBJECT(iHandle); // since I already handle it, this functions reference is irrelevent.
	}
private:
};
