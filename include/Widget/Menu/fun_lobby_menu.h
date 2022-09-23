#pragma once

#include "widget/abstract/fun_menu.h"

namespace fun
{
	namespace Menu
	{
		class LobbyMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<LobbyMenu>
		{
			friend class jgl::Singleton_widget<LobbyMenu>;

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

			LobbyMenu(jgl::Widget* p_parent) : Menu(p_parent)
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