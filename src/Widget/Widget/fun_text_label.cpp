#include "widget/widget/fun_text_label.h"

namespace fun
{
	namespace Widget
	{
		void TextLabel::_render()
		{
			jgl::Text_label::_render();
		}

		void TextLabel::_on_geometry_change()
		{
			jgl::Text_label::_on_geometry_change();
		}

		jgl::Bool TextLabel::_update()
		{
			return (jgl::Text_label::_update());
		}

		jgl::Bool TextLabel::_fixed_update()
		{
			return (jgl::Text_label::_fixed_update());
		}

		TextLabel::TextLabel(jgl::String p_text, jgl::Widget* p_parent) : jgl::Text_label(p_text, p_parent)
		{

		}

		void TextLabel::center_text()
		{
			_label.set_horizontal_align(jgl::Horizontal_alignment::Centred);
			_label.set_vertical_align(jgl::Vertical_alignment::Centred);
		}
	}
}