#include "widget/widget/fun_frame.h"

namespace fun
{
	namespace Widget
	{
		void Frame::_render()
		{
			jgl::Frame::_render();
		}

		void Frame::_on_geometry_change()
		{
			jgl::Frame::_on_geometry_change();
		}

		jgl::Bool Frame::_update()
		{
			return (jgl::Frame::_update());
		}

		jgl::Bool Frame::_fixed_update()
		{
			return (jgl::Frame::_fixed_update());
		}

		Frame::Frame(jgl::Widget* p_parent) : jgl::Frame(p_parent)
		{

		}
	}
}