#pragma once
#include "misc/Storage.h"

class Sudject;

inline std::vector <Sudject*> sudjects;
inline IDirect3DDevice9* Sudevice = nullptr;

enum Type {
	S_TEXT,
	S_SHAPE,
	S_WINDOW,
	S_BUTTON
};

class Sudject {
protected:
	bool visible;
	Sudject* parent;
	std::vector <Sudject*> children;
	Sudject *self = this;
	bool moveable = false;
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
	Sudject* AddChild(Sudject& child) {
		children.push_back(&child);
		child.parent = this;
		return &child;
	}
	Sudject* RemoveChild(int index) {
		Sudject* ch = GetChild(index)->parent = nullptr;
		children.erase(children.begin() + index);
		return ch;
	}
	void RemoveChildren() {
		for (auto& ch : children) {
			ch->parent = nullptr;
		}
		children.clear();
	}
	virtual Type GetType() = 0;
	bool IsVisible() { return visible; }
	virtual void Draw() = 0;
	virtual bool Valid() = 0;
	virtual ScreenPos GetPos() = 0;
	virtual void SetPos(ScreenPos& p) = 0;
	virtual void Move(Vec2 dir) = 0;
	virtual void SetVisible(bool vis) = 0;
	virtual bool IsMoveable() { return moveable; }
	virtual void SetMoveable(bool p) { moveable = p; }
};