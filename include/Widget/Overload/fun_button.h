#pragma once

#include "jgl.h"

namespace fun
{
	namespace Widget
	{
		namespace Overload
		{
			class Button : public jgl::Button
			{
			private:
				void _render()
				{
					jgl::Button::_render();
				}
				void _on_geometry_change()
				{
					jgl::Button::_on_geometry_change();
				}

				jgl::Bool _update()
				{
					return (jgl::Button::_update());
				}
				jgl::Bool _fixed_update()
				{
					return (jgl::Button::_fixed_update());
				}

			public:
				Button(jgl::String p_text, std::function< void(jgl::Data_contener&) > p_funct, jgl::Widget* p_parent) : jgl::Button(p_funct, p_parent)
				{
					_label.set_text(p_text);
				}
			};
		}
	}
}