#include "UIText.h"
#include "UIRenderer.h"

UIText::UIText(const UIAnchor& anchor, const std::string& text, const std::string& fontName, float scale, Color color)
    : UIElement(anchor, Mxm::Vec2i(0, 0)), _color(color), _text(text), _fontName{fontName}, _scale(scale) {

}

void UIText::render(UIRenderer* renderer) const noexcept {
	if (_text.empty()) return;

	renderer->pushText({ (float)getPosition().x, (float)getPosition().y, -0.1f, _scale, _text, _fontName, _color });
}
