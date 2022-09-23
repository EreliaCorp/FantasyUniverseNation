#pragma once

#include "jgl.h"

namespace fun
{
	namespace Widget
	{
		namespace Overload
		{
			class TextEntry : public jgl::Text_entry
			{
			private:
				void _render()
				{
					jgl::Text_entry::_render();
				}
				void _on_geometry_change()
				{
					jgl::Text_entry::_on_geometry_change();
				}

				jgl::Bool _update()
				{
					return (jgl::Text_entry::_update());
				}
				jgl::Bool _fixed_update()
				{
					return (jgl::Text_entry::_fixed_update());
				}

			public:
				TextEntry(jgl::String p_text, jgl::Widget* p_parent) : jgl::Text_entry(p_text, p_parent)
				{

				}
			};
		}
	}
}