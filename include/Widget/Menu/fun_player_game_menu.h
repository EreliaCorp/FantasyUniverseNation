#pragma once

#include "structure/fun_context.h"
#include "widget/abstract/fun_menu.h"

#include "widget/fun_board_renderer.h"

namespace fun
{
	namespace Menu
	{
		class PlayerGameMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<PlayerGameMenu>
		{
			friend class jgl::Singleton_widget<PlayerGameMenu>;

		private:
			fun::Widget::BoardRenderer* _board_renderer;

			void _on_server_instanciation()
			{
				THROW_INFORMATION("On server instanciation [PlayerGameMenu]");
			}

			void _on_client_instanciation()
			{
				THROW_INFORMATION("On client instanciation [PlayerGameMenu]");


				CLIENT_ACTIVITY(fun::Network::ServerMessage::BoardData) {
					fun::Structure::Context::instance()->board.pull(p_msg);

					_board_renderer->update_board();
				});
			}

			void _render()
			{
				_board_renderer->set_geometry(0, _area);
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
				_board_renderer = new fun::Widget::BoardRenderer(this);
				_board_renderer->activate();

				_board_renderer->update_board();
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