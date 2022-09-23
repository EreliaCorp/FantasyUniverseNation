#pragma once

#include "widget/abstract/fun_menu.h"

namespace fun
{
	namespace Menu
	{
		class GameMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<GameMenu>
		{
			friend class jgl::Singleton_widget<GameMenu>;

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

			GameMenu(jgl::Widget* p_parent) : Menu(p_parent)
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