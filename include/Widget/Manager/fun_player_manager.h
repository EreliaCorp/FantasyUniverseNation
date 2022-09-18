#pragma once

#include "jgl.h"

#include "widget/widget/fun_card_renderer.h"

namespace fun
{
	namespace Manager
	{
		class PlayerManager : public jgl::Singleton_widget<PlayerManager>, public jgl::Widget
		{
		public:
			static const jgl::Size_t C_HAND_SIZE = 10u;

			friend class jgl::Singleton_widget<PlayerManager>;
		protected:
			jgl::Size_t _last_selected_card = C_HAND_SIZE;
			fun::Widget::CardRenderer* _player_hand[C_HAND_SIZE];

			void _render();
			void _on_geometry_change();

			jgl::Bool _update();
			jgl::Bool _fixed_update();

			PlayerManager(jgl::Widget* p_parent);
			void highlight_hand_card(jgl::Size_t p_index);
		};
	}
}