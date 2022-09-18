#include "widget/manager/fun_player_manager.h"

namespace fun
{
	namespace Manager
	{
		void PlayerManager::_render()
		{

		}

		void PlayerManager::_on_geometry_change()
		{
			jgl::Vector2Int card_size = jgl::Vector2(300) * fun::Widget::CardRenderer::C_SCREEN_RATIO;
			jgl::Float overlap = card_size.x / 5;
			jgl::Vector2Int placement = jgl::Vector2Int((_area.x - overlap * (C_HAND_SIZE - 1) - card_size.x) / 2, _area.y - overlap * 2);

			for (jgl::Size_t i = 0; i < C_HAND_SIZE; i++)
			{
				_player_hand[i]->set_geometry(placement + jgl::Vector2Int(overlap * i, 0), card_size);
			}
		}

		void PlayerManager::highlight_hand_card(jgl::Size_t p_index)
		{
			for (jgl::Size_t i = 0; i < C_HAND_SIZE; i++)
			{
				if (i != p_index)
					_player_hand[i]->set_depth(10 + i * 10);
				else
					_player_hand[i]->set_depth(10 + C_HAND_SIZE * 10);
			}
		}

		jgl::Bool PlayerManager::_update()
		{
			for (jgl::Int i = C_HAND_SIZE - 1; i >= 0; i--)
			{
				if (_player_hand[i]->active() == true &&
					_player_hand[i]->is_pointed() == true)
				{
					if (_last_selected_card != i)
					{
						highlight_hand_card(i);
					}
					_last_selected_card = i;
					return (true);
				}
			}
			return (false);
		}

		jgl::Bool PlayerManager::_fixed_update()
		{
			return (false);
		}

		PlayerManager::PlayerManager(jgl::Widget* p_parent) : jgl::Widget(p_parent)
		{
			for (jgl::Size_t i = 0; i < C_HAND_SIZE; i++)
			{
				_player_hand[i] = new fun::Widget::CardRenderer(this);
				_player_hand[i]->activate();
			}
			highlight_hand_card(C_HAND_SIZE);
		}
	}
}