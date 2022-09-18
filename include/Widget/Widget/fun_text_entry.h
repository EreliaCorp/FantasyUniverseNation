#pragma once

#include "jgl.h"

namespace fun
{
	namespace Widget
	{
		class TextEntry : public jgl::Text_entry
		{
		private:
			void _render();
			void _on_geometry_change();

			jgl::Bool _update();
			jgl::Bool _fixed_update();

		public:
			TextEntry(jgl::String p_text, jgl::Widget* p_parent);
		};
	}
}