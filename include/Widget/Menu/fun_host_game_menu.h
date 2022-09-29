#pragma once

#include "structure/fun_context.h"
#include "widget/abstract/fun_menu.h"

#include "widget/fun_board_renderer.h"

namespace fun
{
	namespace Menu
	{
		class HostGameMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<HostGameMenu>
		{
			friend class jgl::Singleton_widget<HostGameMenu>;

		private:
			fun::Widget::BoardRenderer* _board_renderer;

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
				_board_renderer->set_geometry(0, _area);
			}

			jgl::Bool _update()
			{
				if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::H) == jgl::Input_status::Release)
				{
					fun::Structure::Context::instance()->board.play_card(
							fun::Structure::Context::instance()->board.deck.draw(),
							jgl::Vector2Int(jgl::generate_nbr(0, fun::Structure::Board::C_SIZE.x), jgl::generate_nbr(0, fun::Structure::Board::C_SIZE.y)
						));
					_board_renderer->update_board();
				}

				return (false);
			}

			jgl::Bool _fixed_update()
			{
				
				return (false);
			}

			HostGameMenu(jgl::Widget* p_parent) : Menu(p_parent)
			{
				_board_renderer = new fun::Widget::BoardRenderer(this);
				_board_renderer->activate();

				for (jgl::Size_t i = 0; i < 30; i++)
				{
					fun::Structure::Context::instance()->board.deck.add_card(fun::Structure::Card::Card());
				}

				for (jgl::Size_t i = 0; i < 4; i++)
				{
					fun::Structure::Context::instance()->board.play_card(
							fun::Structure::Context::instance()->board.deck.draw(), 
							jgl::Vector2Int(jgl::generate_nbr(0, fun::Structure::Board::C_SIZE.x), jgl::generate_nbr(0, fun::Structure::Board::C_SIZE.y)
						));
				}

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