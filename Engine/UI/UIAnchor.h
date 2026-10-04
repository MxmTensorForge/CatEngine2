#ifndef UIANCHOR_H
#define UIANCHOR_H

#include "../Mxm/Vec2.h"
#include "../Mxm/Vec2i.h"

struct UIAnchor final
{
    Mxm::Vec2 pos = Mxm::Vec2();
    Mxm::Vec2i offset = Mxm::Vec2i();

    UIAnchor() = default;
    UIAnchor(const Mxm::Vec2& pos, const Mxm::Vec2i& offset = Mxm::Vec2i()) : pos{pos}, offset{offset} {
        
    }

    UIAnchor operator+(const Mxm::Vec2i& vecOffset) const noexcept {
        return UIAnchor(pos, offset + vecOffset);
    }
    UIAnchor operator-(const Mxm::Vec2i& vecOffset) const noexcept {
        return UIAnchor(pos, offset - vecOffset);
    }

    static UIAnchor topLeft()     { return UIAnchor(Mxm::Vec2(0.0f, 0.0f)); }
    static UIAnchor topCenter()   { return UIAnchor(Mxm::Vec2(0.5f, 0.0f)); }
    static UIAnchor topRight()    { return UIAnchor(Mxm::Vec2(1.0f, 0.0f)); }
    static UIAnchor centerLeft()  { return UIAnchor(Mxm::Vec2(0.0f, 0.5f)); }
    static UIAnchor center()      { return UIAnchor(Mxm::Vec2(0.5f, 0.5f)); }
    static UIAnchor centerRight() { return UIAnchor(Mxm::Vec2(1.0f, 0.5f)); }
    static UIAnchor bottomLeft()  { return UIAnchor(Mxm::Vec2(0.0f, 1.0f)); }
    static UIAnchor bottomCenter(){ return UIAnchor(Mxm::Vec2(0.5f, 1.0f)); }
    static UIAnchor bottomRight() { return UIAnchor(Mxm::Vec2(1.0f, 1.0f)); }
};

#endif
