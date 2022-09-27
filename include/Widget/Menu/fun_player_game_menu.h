#pragma once

#include "structure/fun_context.h"
#include "widget/abstract/fun_menu.h"

namespace fun
{
	namespace Menu
	{
		class PlayerGameMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<PlayerGameMenu>
		{
			friend class jgl::Singleton_widget<PlayerGameMenu>;

		private:

			void _on_server_instanciation()
			{
				THROW_INFORMATION("On server instanciation [PlayerGameMenu]");
			}

			void _on_client_instanciation()
			{
				THROW_INFORMATION("On client instanciation [PlayerGameMenu]");
			}

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

			PlayerGameMenu(jgl::Widget* p_parent) : Menu(p_parent)
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