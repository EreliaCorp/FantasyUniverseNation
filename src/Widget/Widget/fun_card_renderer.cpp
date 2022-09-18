#include "widget/widget/fun_card_renderer.h"

namespace fun
{
	namespace Widget
	{
		void CardRenderer::_render()
		{
			//jgl::cout << "Icon depth : " << _icon_frame->depth() << " background : " << _background->depth() << jgl::endl;
			if (_card != nullptr)
			{

			}
		}

		void CardRenderer::_on_geometry_change()
		{
			_background->set_geometry(0, _area);

			jgl::Float space = _background->box().border_size();
			jgl::Vector2Int icon_pos = space * 2;
			jgl::Vector2Int icon_size = _area.x / 4;

			jgl::Vector2Int name_pos = icon_pos + jgl::Vector2Int(icon_size.x + space, 0);
			jgl::Vector2Int name_size = jgl::Vector2Int(_area.x - name_pos.x - space * 2, icon_size.y);

			jgl::Vector2Int desc_pos = icon_pos + jgl::Vector2Int(0, icon_size.y + space);
			jgl::Vector2Int desc_size = jgl::Vector2Int(_area.x - space * 4, _area.y - icon_size.y - space * 5);

			_icon_frame->set_geometry(icon_pos, icon_size);
			_name_label->set_geometry(name_pos, name_size);
			_desc_label->set_geometry(desc_pos, desc_size);
		}

		jgl::Bool CardRenderer::_update()
		{
			return (false);
		}

		jgl::Bool CardRenderer::_fixed_update()
		{
			return (false);
		}

		CardRenderer::CardRenderer(jgl::Widget* p_parent) : jgl::Widget(p_parent)
		{
			_background = new fun::Widget::Frame(this);
			_background->set_depth(_depth);

			_icon_frame = new fun::Widget::Frame(_background);
			_icon_frame->set_depth(_depth + 2);

			_name_label = new fun::Widget::TextLabel("Default name", _background);
			_name_label->set_depth(_depth + 2);
			_name_label->center_text();

			_desc_label = new fun::Widget::TextLabel("", _background);
			_desc_label->set_depth(_depth + 2);

			set_card(nullptr);
		}

		void CardRenderer::set_card(fun::Structure::Card* p_card)
		{
			_card = p_card;

			if (_card == nullptr)
			{
				_background->desactivate();
				_icon_frame->desactivate();
				_name_label->desactivate();
				_desc_label->desactivate();
			}
			else
			{
				_background->activate();
				_icon_frame->activate();
				_name_label->activate();
				_desc_label->activate();
			}
		}
	}
}