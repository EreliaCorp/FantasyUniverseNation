#pragma once

#include "Utils/fun_network.h"
#include "widget/abstract/fun_menu.h"

namespace fun
{
	namespace Menu
	{
		class HostMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<HostMenu>
		{
			friend class jgl::Singleton_widget<HostMenu>;

		private:
			void _render()
			{

			}

			void _on_geometry_change()
			{

			}

			jgl::Bool _update()
			{
				return (false);
			}

			jgl::Bool _fixed_update()
			{
				return (false);
			}

			HostMenu(jgl::Widget* p_parent) : Menu(p_parent)
			{

			}

		public:

			void on_focus()
			{

			}

			void on_unfocus()
			{
				
			}
		};
	}
}