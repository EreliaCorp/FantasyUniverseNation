#pragma once

#include "jgl.h"

namespace fun
{
	namespace Widget
	{
		namespace Overload
		{
			class Frame : public jgl::Frame
			{
			private:
				void _render()
				{
					jgl::Frame::_render();
				}
				void _on_geometry_change()
				{
					jgl::Frame::_on_geometry_change();
				}

				jgl::Bool _update()
				{
					return (jgl::Frame::_update());
				}
				jgl::Bool _fixed_update()
				{
					return (jgl::Frame::_fixed_update());
				}

			public:
				Frame(jgl::Widget* p_parent) : jgl::Frame(p_parent)
				{

				}
			};
		}
	}
}