#pragma once

#include "Utils/fun_network.h"
#include "widget/abstract/fun_menu.h"
#include "structure/fun_context.h"

namespace fun
{
	namespace Menu
	{
		class HostLobbyMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<HostLobbyMenu>
		{
			friend class jgl::Singleton_widget<HostLobbyMenu>;

		private:

			void _on_server_instanciation()
			{
				THROW_INFORMATION("On server instanciation [HostLobbyMenu]");
				
				fun::Network::ServerManager::instance()->server()->set_logout_function([&](fun::Network::Connection* p_client, jgl::Data_contener& p_param) {
						fun::Structure::Player* player = fun::Structure::Context::instance()->gameRoom.player_by_client(p_client->id());
						if (player != nullptr)
						{
							fun::Structure::Context::instance()->gameRoom.remove_player(player->id);
							_push_player_information();
							_update_player_information();
						}
					});
				SERVER_ACTIVITY(fun::Network::ServerMessage::PlayerJoinRoom) {
					jgl::String username;

					p_msg >> username;

					fun::Structure::Context::instance()->gameRoom.add_player(p_client->id(), username);

					_push_player_information();
					_update_player_information();
				});
			}

			void _on_client_instanciation()
			{
				THROW_INFORMATION("On client instanciation [HostLobbyMenu]");
			}

			fun::Widget::Overload::Frame* _background;
			fun::Widget::Overload::Button* _launch_game_button;
			fun::Widget::Overload::Button* _quit_game_button;

			fun::Widget::Overload::TextLabel* _username_label[4];
			fun::Widget::Overload::Button* _kick_button[4];

			void _render()
			{

			}

			void _on_geometry_change()
			{
				_background->set_geometry(0, _area);

				jgl::Float space = 10;
				jgl::Vector2Int kick_button_size = jgl::Vector2Int(30, 30);
				jgl::Vector2Int launch_button_size = jgl::Vector2Int(((_area.x - space * 4) / 2 - space) / 2, 50);
				jgl::Vector2Int username_label_size = jgl::Vector2Int((_area.x - space * 5) / 2, 50);
				jgl::Vector2Int username_label_pos = jgl::Vector2Int(space * 2, space * 2);

				for (jgl::Size_t i = 0; i < 4; i++)
				{
					jgl::Vector2Int tmp_pos = username_label_pos + jgl::Vector2Int(username_label_size.x + space, _area.y - (username_label_size.y + space * 2) * 2 - space * 1) * jgl::Vector2Int(i % 2, i / 2);
					_username_label[i]->set_geometry(tmp_pos, username_label_size);
					_kick_button[i]->set_geometry(tmp_pos + jgl::Vector2Int(username_label_size.x - kick_button_size.x, 0), kick_button_size);
				}

				_launch_game_button->set_geometry(_area - space * 2 - jgl::Vector2Int(launch_button_size.x * 2 + space, launch_button_size.y), launch_button_size);
				_quit_game_button->set_geometry(_area - space * 2 - launch_button_size, launch_button_size);
			}

			jgl::Bool _update()
			{
				return (false);
			}

			jgl::Bool _fixed_update()
			{
				return (false);
			}

			void _push_player_information()
			{
				fun::Network::Message msg = fun::Network::Message(fun::Network::ServerMessage::GameRoomData);

				fun::Structure::Context::instance()->gameRoom.push(msg);

				_send_message_to_player(msg);
			}

			void _send_message_to_player(const fun::Network::Message& p_msg)
			{
				for (jgl::Size_t i = 0; i < fun::Structure::GameRoom::C_MAX_NB_PLAYER; i++)
				{
					auto client = fun::Network::ServerManager::instance()->server()->connection(fun::Structure::Context::instance()->gameRoom.players[i].client_id);

					if (client != nullptr)
					{
						jgl::cout << "Sending message to player [" << fun::Structure::Context::instance()->gameRoom.players[i].id << "][" << fun::Structure::Context::instance()->gameRoom.players[i].client_id << "]" << jgl::endl;
						client->send(p_msg);
					}
				}
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

			HostLobbyMenu(jgl::Widget* p_parent) : Menu(p_parent)
			{
				_background = new fun::Widget::Overload::Frame(this);
				_background->activate();

				_launch_game_button = new fun::Widget::Overload::Button("Launch", [=](jgl::Data_contener& p_param) {
						if (fun::Structure::Context::instance()->gameRoom.nb_player != 0)
						{
							_send_message_to_player(fun::Network::ServerMessage::GameLaunched);
							fun::Publisher::notify(fun::Event::GoHostGameMenu);
						}
					}, _background);
				_launch_game_button->set_depth(_depth + 8);
				_launch_game_button->activate();

				_quit_game_button = new fun::Widget::Overload::Button("Cancel", [=](jgl::Data_contener& p_param) {
						_send_message_to_player(fun::Network::ServerMessage::ExitGameRoom);
						fun::Publisher::notify(fun::Event::GoMainMenu);
					}, _background);
				_quit_game_button->set_depth(_depth + 8);
				_quit_game_button->activate();

				for (jgl::Size_t i = 0; i < 4; i++)
				{
					_username_label[i] = new fun::Widget::Overload::TextLabel("Empty slot", _background);
					_username_label[i]->set_depth(_depth + 4);
					_username_label[i]->activate();
				}

				for (jgl::Size_t i = 0; i < 4; i++)
				{
					_kick_button[i] = new fun::Widget::Overload::Button("X", [=](jgl::Data_contener& p_param) {
							jgl::cout << "Kicking player [" << i << "]" << jgl::endl;
						}, _background);
					_kick_button[i]->set_depth(_depth + 8);
					_kick_button[i]->activate();
				}
			}

		public:

			void on_focus()
			{
				fun::Structure::Context::instance()->clear();
			}

			void on_unfocus()
			{
				
			}
		};
	}
}