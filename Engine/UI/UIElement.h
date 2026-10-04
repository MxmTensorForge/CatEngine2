#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "../Mxm/Vec2i.h"
#include "UIAnchor.h"

#include "../Core/EngineConsts.h"

class UIRenderer;

class UIElement
{
protected:
    UIAnchor _anchor;
    mutable Mxm::Vec2i _cachedPos;
    mutable bool _isDirty = true;
	
	Mxm::Vec2i _size;
	bool _visible = true;
public:
	virtual ~UIElement() = default;
	virtual void render(UIRenderer* renderer) const noexcept = 0;
	virtual void update() noexcept {}

	UIElement(const UIAnchor& anchor, const Mxm::Vec2i& size)
		: _anchor(anchor), _size(size) {
	}
    UIElement(const Mxm::Vec2i& pos, const Mxm::Vec2i& size)
        : UIElement(UIAnchor(Mxm::Vec2(0.0f, 0.0f), pos), size) {}

	void markDirty() const noexcept { _isDirty = true; }
	void recalcPos() const noexcept {
	    if (!_isDirty) return;
		_cachedPos = Mxm::Vec2i(
		    static_cast<int>(_anchor.pos.x * EngineConsts::STANDART_WIDTH) + _anchor.offset.x,
            static_cast<int>(_anchor.pos.y * EngineConsts::STANDART_HEIGHT) + _anchor.offset.y
		);
	}

	const UIAnchor& getAnchor() const noexcept { return _anchor; }
	void setAnchor(const UIAnchor& anchor) noexcept { _anchor = anchor; }

	void setPosition(const Mxm::Vec2i& pos) noexcept { 
	    _anchor.offset = pos;
		markDirty();
	}
	void addPosition(const Mxm::Vec2i& pos) noexcept { 
        _anchor.offset += pos;
        markDirty();
	}

	void setSize(const Mxm::Vec2i& size) noexcept { _size = size; }
	void addSize(const Mxm::Vec2i& size) noexcept { _size += size; }

	void setVisible(bool visible) noexcept { _visible = visible; }

	const Mxm::Vec2i& getPosition() const noexcept { 
        recalcPos();
        return _cachedPos;
    }
	const Mxm::Vec2i& getSize() const noexcept { 
	    return _size;
	}

	bool getVisible() const noexcept { return _visible; }
	bool isInside(const Mxm::Vec2i& point) const noexcept {
		return point.x >= _cachedPos.x && point.x <= _cachedPos.x + _size.x &&
			point.y >= _cachedPos.y && point.y <= _cachedPos.y + _size.y;
	}
};

#endif // !UIELEMENT_H
