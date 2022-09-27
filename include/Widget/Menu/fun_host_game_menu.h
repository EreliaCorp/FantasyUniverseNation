#pragma once

#include "structure/fun_context.h"
#include "widget/abstract/fun_menu.h"

namespace fun
{
	namespace Menu
	{
		class HostGameMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<HostGameMenu>
		{
			friend class jgl::Singleton_widget<HostGameMenu>;

		private:

			void _on_server_instanciation()
			{
				THROW_INFORMATION("On server instanciation [HostGameMenu]");
			}

			void _on_client_instanciation()
			{
				THROW_INFORMATION("On client instanciation [HostGameMenu]");
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

			HostGameMenu(jgl::Widget* p_parent) : Menu(p_parent)
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