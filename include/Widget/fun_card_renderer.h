#pragma once

#include "jgl.h"

#include "widget/Overload/fun_button.h"
#include "widget/Overload/fun_frame.h"
#include "widget/Overload/fun_text_label.h"
#include "widget/Overload/fun_text_entry.h"

#include "structure/fun_context.h"

namespace fun
{
	namespace Widget
	{
		class CardRenderer : public jgl::Widget
		{
		private:
			fun::Widget::Overload::Frame* _background;
			fun::Widget::Overload::Frame* _icon;
			fun::Widget::Overload::TextLabel* _name_label;

			fun::Structure::PlayedCard* _card;

			void _render()
			{

			}
			void _on_geometry_change()
			{
				jgl::Size_t space = _background->box().border_size();

				jgl::Vector2Int background_pos = 0;
				jgl::Vector2Int background_size = _area;

				jgl::Vector2Int icon_size = (_area.x - space * 4) / 5;
				jgl::Vector2Int icon_pos = space * 2;

				jgl::Vector2Int name_size = jgl::Vector2Int(_area.x - space * 5 - icon_size.x, icon_size.y);
				jgl::Vector2Int name_pos = icon_pos + jgl::Vector2Int(icon_size.x + space, 0);

				_background->set_geometry(background_pos, background_size);
				_icon->set_geometry(icon_pos, icon_size);
				_name_label->set_geometry(name_pos, name_size);
			}

			jgl::Bool _update()
			{
				return (false);
			}
			jgl::Bool _fixed_update()
			{
				return (false);
			}

		public:
			CardRenderer(jgl::Widget* p_parent) : jgl::Widget(p_parent)
			{
				_background = new fun::Widget::Overload::Frame(this);
				_background->activate();

				_icon = new fun::Widget::Overload::Frame(_background);
				//_icon->box().set_background_color(jgl::Color::red());
				_icon->box().set_border_size(1);
				_icon->activate();

				_name_label = new fun::Widget::Overload::TextLabel("Base text", _background);
				//_name_label->box().set_background_color(jgl::Color::green());
				_name_label->center_text();
				_name_label->box().set_border_size(1);
				_name_label->activate();
			}

			fun::Structure::PlayedCard* card()
			{
				return (_card);
			}

			void set_card(fun::Structure::PlayedCard* p_card)
			{
				_card = p_card;
				if (_card != nullptr)
				{
					_name_label->label().set_text(_card->card.name);
				}
			}
		};
	}
}