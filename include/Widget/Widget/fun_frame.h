#pragma once

#include "jgl.h"

namespace fun
{
	namespace Widget
	{
		class Frame : public jgl::Frame
		{
		private:
			void _render();
			void _on_geometry_change();

			jgl::Bool _update();
			jgl::Bool _fixed_update();

		public:
			Frame(jgl::Widget* p_parent);
		};
	}
}