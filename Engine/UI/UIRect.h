#ifndef UIRECT_H
#define UIRECT_H

#include "UIElement.h"
#include "../Graphics/Color.h"

class UIRect final : public UIElement
{
private:
	Color _color;
public:
	UIRect(const UIAnchor& anchor, const Mxm::Vec2i& size, Color color);
	void render(UIRenderer* renderer) const noexcept override;

	void setColor(Color color) noexcept { _color = color; }
	Color getColor() const noexcept { return _color; }
};

#endif // !UIRECT_H
