#pragma once

#include "jgl.h"

namespace fun
{
	namespace Widget
	{
		class TextLabel : public jgl::Text_label
		{
		private:
			void _render();
			void _on_geometry_change();

			jgl::Bool _update();
			jgl::Bool _fixed_update();

		public:
			TextLabel(jgl::String p_text, jgl::Widget* p_parent);

			void center_text();
		};
	}
}