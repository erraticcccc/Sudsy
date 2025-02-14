#pragma once
#include "misc/Storage.h"

class Sudject;

inline std::vector <Sudject*> sudjects;
inline IDirect3DDevice9* Sudevice = nullptr;

class Sudject {
protected:
	bool visible;
	Sudject* parent;
	std::vector <Sudject*> children;
public:
	Sudject() {
		parent = nullptr;
		visible = true;
		sudjects.push_back(this);
	}
	Sudject(Sudject* p) {
		parent = p;
		visible = true;
		sudjects.push_back(this);
	}
	Sudject* GetParent() {
		return parent;
	}
	std::vector <Sudject*> GetChildren() {
		return children;
	}
	Sudject* GetChild(int index) {
		return children[index];
	}
	void AddChild(Sudject& child) {
		children.push_back(&child);
		child.parent = this;
	}
	bool IsVisible() { return visible; }
	virtual void Draw() = 0;
	virtual bool Valid() = 0;
	virtual ScreenPos GetPos() = 0;
	virtual void SetVisible(bool vis) = 0;
};