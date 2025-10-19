#pragma once
#include "CScaleform.h"
#include <Project - The Framework\ExpandedExpressions\BoundedWhile.h>
#include <algorithm>

class CScaleformManager {
	struct sMovieRef {
		std::vector<CScaleform*> References;
		int RefCounters;
	};
public:
	CScaleformManager() {

	}
	CScaleform* GetScaleform(const char* name) {
		int movie = GRAPHICS::REQUEST_SCALEFORM_MOVIE(name);
		auto res = BoundedWhile([&]() { return !GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(movie); }, 10, [&](bool b, int c) {
			hudLogf("[Scaleform] Loading Scaleform: %s", name);
			movie = GRAPHICS::REQUEST_SCALEFORM_MOVIE(name);
			WAIT(0);
			});
		auto scl = new CScaleform(movie);
		m_Scaleforms[name].References.push_back(scl);
		m_Scaleforms[name].RefCounters++;
		return scl;
	}
	void ReleaseScaleform(CScaleform* scaleform) {
		for (auto& [key, val] : m_Scaleforms) {
			auto res = std::find(val.References.begin(), val.References.end(), scaleform);
			if (res == val.References.end()) {
				hudWarnf("Scaleform was not found. Did you create it through CScaleformManager?");
				return; // did not find Scaleform. 
			}
			val.References.erase(res);
			delete *res;
			val.RefCounters--; // no other scaleform
			if (val.RefCounters <= 0 && val.References.size() <= 0) {
				m_Scaleforms.erase(key);
			}
		}
	}
	~CScaleformManager() {
		for (auto& [key, val] : m_Scaleforms) {
			for (auto* v : val.References) {
				delete v;
			}
			val.References.clear();
			val.RefCounters = 0;
		}
		m_Scaleforms.clear();
	}
	const std::unordered_map<std::string, sMovieRef>& GetScaleforms() {
		return this->m_Scaleforms;
	}
private:

	std::unordered_map<std::string, sMovieRef> m_Scaleforms;
};