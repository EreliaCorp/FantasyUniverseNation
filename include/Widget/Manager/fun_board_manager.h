#pragma once

#include "jgl.h"
#include "widget/Widget/fun_board_renderer.h"

namespace fun
{
	namespace Manager
	{
		class BoardManager : public jgl::Singleton_widget<BoardManager>, public jgl::Widget
		{
			friend class jgl::Singleton_widget<BoardManager>;

		protected:
			fun::Widget::BoardRenderer* _board_renderer;

			void _render();
			void _on_geometry_change();

			jgl::Bool _update();
			jgl::Bool _fixed_update();
			BoardManager(jgl::Widget* p_parent);
		};
	}
}