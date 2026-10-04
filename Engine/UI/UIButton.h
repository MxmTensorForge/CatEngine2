#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "UIText.h"
#include "UIRect.h"

#include <functional>
#include <memory>

class UIButton final : public UIElement
{
private:
	std::unique_ptr<UIRect> _background;
	std::unique_ptr<UIText> _text;
	Mxm::Vec2i _textOffset;

	std::function<void()> _onPress = nullptr;
	std::function<void()> _onHover = nullptr;
	std::function<void()> _onDown = nullptr;
	std::function<void()> _onUpdate = nullptr;
	bool _isHover = false;

	Color _baseColor;
	Color _hoverColor;
	Color _downedColor;
public:
	UIButton(const UIAnchor& anchor, const Mxm::Vec2i& size, const std::string& text = "", const std::string& fontName = "", 
	    const Mxm::Vec2i& textOffset = Mxm::Vec2i(), float textScale = 1.0f,
		Color textColor = Color(255, 255, 255), Color baseColor = Color(0, 0, 0), Color hoverColor = Color(40, 40, 40), Color downedColor = Color(60, 100, 15));
	void render(UIRenderer* renderer) const noexcept override;
	void update() noexcept override;

	void setPosition(const Mxm::Vec2i& pos) noexcept;
	void setSize(const Mxm::Vec2i& size) noexcept;

	void setTextOffset(const Mxm::Vec2i& offset) noexcept { _textOffset = offset; }
	void setTextScale(int scale) noexcept { _text->setScale(scale); }

	void setText(const std::string& text) noexcept { _text->setText(text); }

	void setOnPress(const std::function<void()>& func) noexcept { _onPress = func; }
	void setOnHover(const std::function<void()>& func) noexcept { _onHover = func; }
	void setOnDown(const std::function<void()>& func) noexcept { _onDown = func; }
	void setOnUpdate(const std::function<void()>& func) noexcept { _onUpdate = func; }

	void setBaseColor(Color color) { _baseColor = color; }
	Color getBaseColor() { return _baseColor; }
	void setHoverColor(Color color) { _hoverColor = color; }
	Color getHoverColor() { return _hoverColor; }
	void setDownedColor(Color color) { _downedColor = color; }
	Color getDownedColor() { return _downedColor; }
};

#endif // !UIBUTTON_H
