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

			jgl::Timer _update_message_timer = jgl::Timer(10);

			jgl::Float _top_depth = 10;
			jgl::Vector2Int _delta_anchor;
			fun::Widget::CardRenderer* _selected_card;

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
							fun::Structure::Context::instance()->deck.draw(),
							jgl::Vector2Int(jgl::generate_nbr(10, fun::Structure::Board::C_SIZE.x - 10), jgl::generate_nbr(10, fun::Structure::Board::C_SIZE.y - 10)),
							_top_depth
						);
					_board_renderer->update_board();
					_top_depth++;
					fun::Publisher::instance()->notify(fun::Event::OnBoardEdition);
				}

				if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Pressed)
				{
					_selected_card = _board_renderer->selected_card();

					if (_selected_card != nullptr)
					{
						_delta_anchor = jgl::Vector2(_selected_card->anchor() - jgl::Application::active_application()->mouse().pos()) / _board_renderer->card_unit();
						_top_depth++;
						_selected_card->card()->level = _top_depth;
						_board_renderer->update_board();
					}
				}

				if (_selected_card != nullptr)
				{
					static jgl::Vector2Int old_pos = -1;

					jgl::Vector2Int tmp = jgl::Application::active_application()->mouse().pos();

					if (old_pos != tmp && jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Down)
					{
						jgl::Vector2 tmp_delta = jgl::Vector2(tmp) / _board_renderer->card_unit();
						_selected_card->card()->pos = tmp_delta + _delta_anchor;
						_board_renderer->update_board();

						fun::Publisher::instance()->notify(fun::Event::OnBoardEdition);
					}

					old_pos = tmp;
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
					fun::Structure::Context::instance()->deck.add_card(fun::Structure::Card::Card());
				}

				_top_depth = 1;
				for (jgl::Size_t i = 0; i < 4; i++)
				{

					fun::Structure::Context::instance()->board.play_card(
							fun::Structure::Context::instance()->deck.draw(),
							jgl::Vector2Int(jgl::generate_nbr(10, fun::Structure::Board::C_SIZE.x - 10), jgl::generate_nbr(10, fun::Structure::Board::C_SIZE.y - 10)),
							_top_depth
						);
					_top_depth++;
				}
				_board_renderer->update_board();

				fun::Publisher::instance()->subscribe(fun::Event::OnBoardEdition, [&]() {
						fun::Network::Message msg(fun::Network::ServerMessage::BoardData);

						fun::Structure::Context::instance()->board.push(msg);

						fun::Structure::Context::instance()->gameRoom.send_message(msg);
					});
			}

		public:

			void on_focus()
			{
				fun::Publisher::instance()->notify(fun::Event::OnBoardEdition);
			}

			void on_unfocus()
			{

			}
		};
	}
}