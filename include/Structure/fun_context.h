#pragma once

#include "jgl.h"

#include "Utils/fun_network.h"

namespace fun
{
	namespace Structure
	{
		struct Player
		{
			jgl::Long id;
			jgl::Long client_id;
			jgl::String username;

			friend jgl::Stream& operator<<(jgl::Stream& os, const Player& value)
			{
				os << value.username << " : id [" << value.id << "] / Client id [" << value.client_id << "]";
				return os;
			}

			void push(fun::Network::Message& p_msg)
			{
				p_msg << id;
				p_msg << username;
			}

			void pull(fun::Network::Message& p_msg)
			{
				p_msg >> id;
				p_msg >> username;
			}
		};

		struct GameRoom
		{
			static inline const jgl::Size_t C_MAX_NB_PLAYER = 4u;

			jgl::Size_t nb_player;
			Player players[C_MAX_NB_PLAYER];

			void add_player(jgl::Long p_client_id, jgl::String p_username)
			{
				if (nb_player < C_MAX_NB_PLAYER)
				{
					jgl::Size_t index;
					for (index = 0; index < C_MAX_NB_PLAYER && players[index].client_id != 0; index++);
					players[index].client_id = p_client_id;
					players[index].id = index;
					players[index].username = p_username;
					nb_player++;
				}
			}
			void remove_player(jgl::Long p_id)
			{
				players[p_id].client_id = 0;
				players[p_id].id = 0;
				players[p_id].username = "";
				nb_player--;
			}

			Player* player_by_client(jgl::Long id)
			{
				for (jgl::Size_t i = 0; i < nb_player; i++)
				{
					if (players[i].client_id == id)
					{
						return (&players[i]);
					}
				}
				return (nullptr);
			}
			Player* player_by_id(jgl::Long id)
			{
				for (jgl::Size_t i = 0; i < nb_player; i++)
				{
					if (players[i].id == id)
					{
						return (&players[i]);
					}
				}
				return (nullptr);
			}

			friend jgl::Stream& operator<<(jgl::Stream& os, const GameRoom& value)
			{
				for (jgl::Size_t i = 0; i < C_MAX_NB_PLAYER; i++)
				{
					os << value.players[i] << jgl::endl;
				}
				return os;
			}

			void push(fun::Network::Message& p_msg)
			{
				p_msg << nb_player;
				for (jgl::Size_t i = 0; i < C_MAX_NB_PLAYER; i++)
				{
					players[i].push(p_msg);
				}
			}

			void pull(fun::Network::Message& p_msg)
			{
				p_msg >> nb_player;
				for (jgl::Size_t i = 0; i < C_MAX_NB_PLAYER; i++)
				{
					players[i].pull(p_msg);
				}
			}
		};

		struct Card
		{
			Card()
			{

			}
		};

		struct Board
		{
			jgl::Array<fun::Structure::Card> played_cards;

			Board()
			{

			}
		};

		struct Context : public jgl::Singleton<Context>
		{
			jgl::String username;
			jgl::String address;

			GameRoom gameRoom;
			Board board;

			void clear()
			{
				THROW_INFORMATION("Clearing global context");

				username = "";
				address = "";
			}
		};
	}
}