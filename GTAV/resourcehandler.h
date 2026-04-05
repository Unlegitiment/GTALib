#pragma once
#include <ModCore/utils/Copy.h>
class gtaResourceHandler {
public:
	static constexpr Entity NULL_HANDLE = 0;
	gtaResourceHandler() = default;
	gtaResourceHandler(Entity& iEnt) : m_EntityHandle(iEnt) { iEnt = 0; };
	gtaResourceHandler(gtaResourceHandler&& obj) : m_EntityHandle(obj.m_EntityHandle) {
		obj.m_EntityHandle = NULL_HANDLE;
	}
	NO_COPY(gtaResourceHandler);
	virtual ~gtaResourceHandler() = default;
	gtaResourceHandler& operator=(gtaResourceHandler&& obj) {
		if (this != &obj) {
			if (this->IsHandlingAResource()) {
				this->Delete();
			}
			m_EntityHandle = obj.m_EntityHandle;
			obj.m_EntityHandle = NULL_HANDLE;
		}
		return *this;
	}
	Entity GetHandle() const {
		return this->m_EntityHandle;
	}
	void Delete() {
		if (this->IsHandlingAResource()) {
			this->DeleteInternal();
			this->m_EntityHandle = NULL_HANDLE;
		}
	}
	bool IsHandlingAResource() const {
		return this->m_EntityHandle != NULL_HANDLE;
	}
protected:
	/*
		Allows for diversification on how the process should be handled, but does not conflate the knowledge of the live resource with m_EntityHandle's scope.
	*/
	virtual void DeleteInternal() = 0;
	gtaResourceHandler(const Entity& ent) : m_EntityHandle(ent) {}
private:
	Entity m_EntityHandle = NULL_HANDLE; // this is much more of a convenience is it worth it?
};
