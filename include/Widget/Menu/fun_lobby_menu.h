#pragma once

#include "Utils/fun_network.h"
#include "Utils/fun_event_manager.h"
#include "widget/abstract/fun_menu.h"

namespace fun
{
	namespace Menu
	{
		class LobbyMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<LobbyMenu>
		{
			friend class jgl::Singleton_widget<LobbyMenu>;

		private:
			fun::Widget::Overload::Frame* _background;

			fun::Widget::Overload::TextLabel* _username_label[4];

			void _on_server_instanciation()
			{
				THROW_INFORMATION("On server instanciation [LobbyMenu]");
			}

			void _on_client_instanciation()
			{
				THROW_INFORMATION("On client instanciation [LobbyMenu]");

				CLIENT_ACTIVITY(fun::Network::ServerMessage::GameRoomData) {
					fun::Structure::Context::instance()->gameRoom.pull(p_msg);
					_update_player_information();
				});
			}

			void _render()
			{

			}

			void _on_geometry_change()
			{
				_background->set_geometry(0, _area);

				jgl::Float space = 10;
				jgl::Vector2Int username_label_size = jgl::Vector2Int((_area.x - space * 5) / 2, 50);
				jgl::Vector2Int username_label_pos = jgl::Vector2Int(space * 2, space * 2);

				for (jgl::Size_t i = 0; i < 4; i++)
				{
					_username_label[i]->set_geometry(username_label_pos + jgl::Vector2Int(username_label_size.x + space, _area.y - username_label_size.y - space * 4) * jgl::Vector2Int(i % 2, i / 2), username_label_size);
				}
			}

			jgl::Bool _update()
			{				
				return (false);
			}

			jgl::Bool _fixed_update()
			{
				return (false);
			}

			void _update_player_information()
			{
				for (jgl::Size_t i = 0; i < fun::Structure::Context::instance()->gameRoom.C_MAX_NB_PLAYER; i++)
				{
					if (fun::Structure::Context::instance()->gameRoom.players[i].username == "")
					{
						_username_label[i]->label().set_text("Empty slot");
						_username_label[i]->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
					}
					else
					{
						_username_label[i]->label().set_text(fun::Structure::Context::instance()->gameRoom.players[i].username);
						_username_label[i]->label().set_horizontal_align(jgl::Horizontal_alignment::Left);
					}
				}
			}

			LobbyMenu(jgl::Widget* p_parent) : Menu(p_parent)
			{
				_background = new fun::Widget::Overload::Frame(this);
				_background->activate();

				for (jgl::Size_t i = 0; i < 4; i++)
				{
					_username_label[i] = new fun::Widget::Overload::TextLabel("Empty slot", _background);
					_username_label[i]->set_depth(_depth + 4);
					_username_label[i]->activate();
				}

				fun::Publisher::subscribe(fun::Event::JoinRoom, [&]() {
						fun::Network::Message msg = fun::Network::Message(fun::Network::ServerMessage::PlayerJoinRoom);

						msg << fun::Structure::Context::instance()->username;

						fun::Network::ClientManager::send(msg);
					});
			}

		public:

			void on_focus()
			{
				fun::Publisher::notify(fun::Event::CheckConnection);
			}

			void on_unfocus()
			{

			}
		};
	}
}