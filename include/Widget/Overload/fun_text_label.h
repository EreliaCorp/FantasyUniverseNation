#pragma once

#include "jgl.h"

namespace fun
{
	namespace Widget
	{
		namespace Overload
		{
			class TextLabel : public jgl::Text_label
			{
			private:
				void _render()
				{
					jgl::Text_label::_render();
				}
				void _on_geometry_change()
				{
					jgl::Text_label::_on_geometry_change();
				}

				jgl::Bool _update()
				{
					return (jgl::Text_label::_update());
				}
				jgl::Bool _fixed_update()
				{
					return (jgl::Text_label::_fixed_update());
				}

			public:
				TextLabel(jgl::String p_text, jgl::Widget* p_parent) : jgl::Text_label(p_text, p_parent)
				{

				}

				void center_text()
				{
					_label.set_horizontal_align(jgl::Horizontal_alignment::Centred);
					_label.set_vertical_align(jgl::Vertical_alignment::Centred);
				}
			};
		}
	}
}