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

			fun::Structure::Card* _card;

			void _render()
			{

			}
			void _on_geometry_change()
			{
				jgl::Vector2Int background_pos = _anchor;
				jgl::Vector2Int background_size = _area;

				_background->set_geometry(0, background_size);
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
			}

			void set_card(fun::Structure::Card* p_card)
			{
				_card = p_card;
			}
		};
	}
}