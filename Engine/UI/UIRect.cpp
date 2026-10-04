#include "UIRect.h"
#include "UIRenderer.h"

UIRect::UIRect(const UIAnchor& anchor, const Mxm::Vec2i& size, Color color) : UIElement(anchor, size), _color(color) {

}

void UIRect::render(UIRenderer* renderer) const noexcept {
	renderer->pushRect({ (float)getPosition().x, (float)getPosition().y, 0.0f, (float)_size.x, (float)_size.y, _color });
}
