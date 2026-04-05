#pragma once
#include <ModCore/thirdparty/ScriptHook/include/types.h>
#include <string>
#include <ModCore/thirdparty/ScriptHook/include/natives.h>
namespace rage {
	class HashString {
	public:
		static constexpr size_t MaxLen = 256;
		HashString() = default;
		HashString(const char* Source) {
			m_String = Source;
			m_Hash = MISC::GET_HASH_KEY(m_String.c_str());
		}
		Hash ToHash() const {
			return m_Hash; // is this slow? yes. would it be quicker to just steal some hash impl from some other mod, yes. fuck you.
		}
		const char* GetString() const {
			return m_String.c_str(); // DON'T YOU DARE TOUCH MAH SPAGHET!
		}
		~HashString() {}
	private:
		std::string m_String;
		Hash m_Hash = NULL;
	};
}