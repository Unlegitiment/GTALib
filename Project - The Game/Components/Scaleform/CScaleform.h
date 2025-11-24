#pragma once
#include <string>
#include <vector>
#include <Project - The Game\SHV\natives.h>
#include <Project - The Framework\renderer\fwRenderable.h>
#include <Project - The Game\Components\hud_common.h>
class CScaleform {
public:
	CScaleform(int handle) {
		this->m_Handle = handle;
	}
	CScaleform& BeginMethod(const char* name) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->m_Handle, name);
		return *this;
	}
	template<typename T>
	CScaleform& Call(T) {
		hudLogf("Parameter not recognized! %s", typeid(T).name());
		return *this;
	}
	// DO NOT CALL THIS! BROKEN!
	template<typename... Args> [[deprecated("Call<Args&&...> is broken. This will not Call into the Target Scaleform.")]] CScaleform& Call(Args&&... data) {
		Call((data)...);
		return *this;
	}
	template<>  CScaleform& Call<const char*>(const char* data) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(data);
		return *this;
	}
	template<> CScaleform& Call<int>(int data) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(data);
		return *this;
	}
	template<> CScaleform& Call<float>(float data) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(data);
		return *this;
	}
	template<> CScaleform& Call<bool>(bool b) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(b);
		return *this;
	}
	void FinalizeCall() {
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	int FinalizeCallWithReturnInt() {
		return GRAPHICS::GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT(GetSclReturnHandle());
	}
	bool FinalizeCallWithReturnBool() {
		return GRAPHICS::GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL(GetSclReturnHandle());
	}
	const char* FinalizeCallWithReturnString() {
		return GRAPHICS::GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING(GetSclReturnHandle());
	}
	int GetHandle() {
		return this->m_Handle;
	}
	operator int() {
		return this->m_Handle;
	}
private:
	int GetSclReturnHandle() {
		int _Handle_ = GRAPHICS::END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE();
		while (!GRAPHICS::IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY(_Handle_)) {
			WAIT(0);
		}
		return _Handle_;
	}
	int m_Handle = 0;
};