#include "UIButton.h"
#include "../Core/Input.h"

UIButton::UIButton(const UIAnchor& anchor, const Mxm::Vec2i& size,
	const std::string& text, const std::string& fontName, const Mxm::Vec2i& textOffset, float textScale, Color textColor,
	Color baseColor, Color hoverColor, Color downedColor)
	: UIElement(anchor, size), _textOffset(textOffset),
	_baseColor(baseColor), _hoverColor(hoverColor), _downedColor(downedColor)
{
	_background = std::make_unique<UIRect>(anchor, size, baseColor);
	_text = std::make_unique<UIText>(UIAnchor(anchor.pos, anchor.offset + _textOffset), text, fontName, textScale, textColor);
}

void UIButton::setPosition(const Mxm::Vec2i& pos) noexcept {
	UIElement::setPosition(pos);
	if (_background) _background->setPosition(pos);
	if (_text)       _text->setPosition(pos + _textOffset);
}

void UIButton::setSize(const Mxm::Vec2i& size) noexcept {
	UIElement::setSize(size);
	if (_background) _background->setSize(size);
	if (_text)       _text->setSize(size);
}

void UIButton::render(UIRenderer* renderer) const noexcept {
	_background->render(renderer);
	_text->render(renderer);
}
void UIButton::update() noexcept {
	Mxm::Vec2 mousePos = Input::getMousePosition();

	bool hovered = !Input::getMouseLockState() && isInside(Mxm::Vec2i(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y)));
	bool pressed = hovered && Input::isMouseButtonReleased(MouseButton::MOUSE0);
	bool downed = hovered && Input::isMouseButtonDown(MouseButton::MOUSE0);

	if (downed)       _background->setColor(_downedColor);
	else if (hovered) _background->setColor(_hoverColor);
	else              _background->setColor(_baseColor);

	if (pressed && _onPress) _onPress();
	if (downed && _onDown)   _onDown();

	if (!_isHover && hovered) {
		_isHover = true;
		if (_onHover) _onHover();
	}
	if (_isHover && !hovered) {
		_isHover = false;
	}

	if (_onUpdate) _onUpdate();
}
