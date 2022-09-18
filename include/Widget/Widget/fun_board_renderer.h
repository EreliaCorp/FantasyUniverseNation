#pragma once

#include "jgl.h"
#include "widget/widget/fun_frame.h"
#include "widget/widget/fun_card_renderer.h"

namespace fun
{
	namespace Widget
	{
		class BoardRenderer : public jgl::Widget
		{
		private:
			fun::Widget::Frame* _background;
			jgl::Array<fun::Widget::CardRenderer*> _active_cards;

			void _render();
			void _on_geometry_change();

			jgl::Bool _update();
			jgl::Bool _fixed_update();

		public:
			BoardRenderer(jgl::Widget* p_parent);
		};
	}
}