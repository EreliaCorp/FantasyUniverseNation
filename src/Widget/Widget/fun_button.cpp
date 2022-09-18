#include "widget/widget/fun_button.h"

namespace fun
{
	namespace Widget
	{
		void Button::_render()
		{
			jgl::Button::_render();
		}

		void Button::_on_geometry_change()
		{
			jgl::Button::_on_geometry_change();
		}

		jgl::Bool Button::_update()
		{
			return (jgl::Button::_update());
		}

		jgl::Bool Button::_fixed_update()
		{
			return (jgl::Button::_fixed_update());
		}

		Button::Button(std::function< void(jgl::Data_contener&) > p_funct, jgl::Widget* p_parent) : jgl::Button(p_funct, p_parent)
		{

		}
	}
}