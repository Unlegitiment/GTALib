#pragma once
#include <vector>
#include <Project - The Framework\renderer\fwRenderable.h>
class Renderer {
public:
	void Render() {
		for (auto renderable : m_Renderables) {
			renderable->Render();
		}
	}
	void Add(fwRenderable* a) {
		this->m_Renderables.push_back(a);
	}
	std::vector<fwRenderable*>& GetList() { return m_Renderables; }
	void Remove(fwRenderable* rd) {
		auto res = std::find(m_Renderables.begin(), m_Renderables.end(), rd);
		if (res == m_Renderables.end()) {
			renderLogf("Did not find renderable");
			return;
		}
		m_Renderables.erase(res);

	}
private:
	std::vector<fwRenderable*> m_Renderables;
};