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

			void send_message(const fun::Network::Message& p_msg)
			{
				for (jgl::Size_t i = 0; i < C_MAX_NB_PLAYER; i++)
				{
					auto client = fun::Network::ServerManager::instance()->server()->connection(players[i].client_id);

					if (client != nullptr)
					{
						client->send(p_msg);
					}
				}
			}
		};

		struct Card
		{
			jgl::String name;

			Card()
			{
				for (jgl::Size_t i = 0; i < 6; i++)
				{
					name.push_back(jgl::Glyph(jgl::Int(jgl::generate_nbr(65, 89))));
				}
			}

			void push(fun::Network::Message& p_msg)
			{
				p_msg << name;
			}

			void pull(fun::Network::Message& p_msg)
			{
				p_msg >> name;
			}
		};

		class Deck
		{
		private:
			jgl::Size_t index;
			jgl::Array<Card> cards;

		public:
			jgl::Size_t size() { return (cards.size()); }

			void add_card(Card p_card)
			{
				cards.push_back(p_card);
			}

			Card draw()
			{
				Card result = cards[index % cards.size()];
				
				index++;

				return (result);
			}

			void shuffle()
			{

			}

			void push(fun::Network::Message& p_msg)
			{
				p_msg << index;
				p_msg << size();
				for (jgl::Size_t i = 0; i < cards.size(); i++)
				{
					cards[i].push(p_msg);
				}
			}

			void pull(fun::Network::Message& p_msg)
			{
				jgl::Size_t size;

				p_msg >> index;
				p_msg >> size;
				cards.resize(size);
				for (jgl::Size_t i = 0; i < size; i++)
				{
					cards[i].pull(p_msg);
				}
			}
		};

		struct PlayedCard
		{
			Card card;
			jgl::Vector2 pos;
			jgl::Size_t level;

			void push(fun::Network::Message& p_msg)
			{
				card.push(p_msg);
				p_msg << pos;
				p_msg << level;
			}

			void pull(fun::Network::Message& p_msg)
			{
				card.pull(p_msg);
				p_msg >> pos;
				p_msg >> level;
			}
		};

		struct Board
		{
			static inline const jgl::Vector2 C_SIZE = jgl::Vector2(100, 70);

			jgl::Array<fun::Structure::PlayedCard> played_cards;

			Board()
			{
				
			}

			void play_card(const fun::Structure::Card& p_card, jgl::Vector2 p_pos, jgl::Size_t p_level)
			{
				fun::Structure::PlayedCard tmp_card;

				tmp_card.card = p_card;
				tmp_card.pos = p_pos;
				tmp_card.level = p_level;

				played_cards.push_back(tmp_card);
			}

			void push(fun::Network::Message& p_msg)
			{
				p_msg << static_cast<jgl::Size_t>(played_cards.size());

				for (jgl::Size_t i = 0; i < played_cards.size(); i++)
				{
					played_cards[i].push(p_msg);
				}
			}

			void pull(fun::Network::Message& p_msg)
			{
				jgl::Size_t nb_card;

				p_msg >> nb_card;
				played_cards.resize(nb_card);
				for (jgl::Size_t i = 0; i < nb_card; i++)
				{
					played_cards[i].pull(p_msg);
				}
			}
		};

		struct Context : public jgl::Singleton<Context>
		{
			jgl::String username;
			jgl::String address;

			GameRoom gameRoom;
			Board board;
			Deck deck;

			void clear()
			{
				THROW_INFORMATION("Clearing global context");

				username = "";
				address = "";
			}
		};
	}
}