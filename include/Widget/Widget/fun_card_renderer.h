#pragma once

#include "widget/widget/fun_frame.h"
#include "widget/widget/fun_text_label.h"
#include "structure/fun_card.h"

namespace fun
{
	namespace Widget
	{
		class CardRenderer : public jgl::Widget
		{
		public:
			static inline const jgl::Vector2 C_SCREEN_RATIO = jgl::Vector2(0.78f, 1);

		private:
			fun::Widget::Frame* _background;
			fun::Widget::Frame* _icon_frame;
			fun::Widget::TextLabel* _name_label;
			fun::Widget::TextLabel* _desc_label;

			fun::Structure::Card* _card;

			void _render();
			void _on_geometry_change();

			jgl::Bool _update();
			jgl::Bool _fixed_update();

		public:
			CardRenderer(jgl::Widget* p_parent);

			void set_card(fun::Structure::Card* p_card);
		};
	}
}