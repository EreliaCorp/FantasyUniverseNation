#include "widget/widget/fun_board_renderer.h"

namespace fun
{
	namespace Widget
	{
		void BoardRenderer::_render()
		{

		}

		void BoardRenderer::_on_geometry_change()
		{
			_background->set_geometry(0, _area);
		}

		jgl::Bool BoardRenderer::_update()
		{
			return (false);
		}

		jgl::Bool BoardRenderer::_fixed_update()
		{
			return (false);
		}

		BoardRenderer::BoardRenderer(jgl::Widget* p_parent) : jgl::Widget(p_parent)
		{
			_background = new fun::Widget::Frame(this);
			_background->box().set_color(jgl::Color(227, 185, 129), jgl::Color(173, 145, 108));
			_background->activate();
		}
	}
}