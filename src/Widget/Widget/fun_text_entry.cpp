#include "widget/widget/fun_text_entry.h"

namespace fun
{
	namespace Widget
	{
		void TextEntry::_render()
		{
			jgl::Text_entry::_render();
		}

		void TextEntry::_on_geometry_change()
		{
			jgl::Text_entry::_on_geometry_change();
		}

		jgl::Bool TextEntry::_update()
		{
			return (jgl::Text_entry::_update());
		}

		jgl::Bool TextEntry::_fixed_update()
		{
			return (jgl::Text_entry::_fixed_update());
		}

		TextEntry::TextEntry(jgl::String p_text, jgl::Widget* p_parent) : jgl::Text_entry(p_text, p_parent)
		{

		}
	}
}