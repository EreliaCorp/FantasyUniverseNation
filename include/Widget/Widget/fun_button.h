#pragma once

#include "jgl.h"

namespace fun
{
	namespace Widget
	{
		class Button : public jgl::Button
		{
		private:
			void _render();
			void _on_geometry_change();

			jgl::Bool _update();
			jgl::Bool _fixed_update();

		public:
			Button(std::function< void(jgl::Data_contener&) > p_funct, jgl::Widget* p_parent);
		};
	}
}