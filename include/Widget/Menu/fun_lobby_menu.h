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