#pragma once

#include "Utils/fun_network.h"
#include "widget/abstract/fun_menu.h"

namespace fun
{
	namespace Menu
	{
		class HostMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<HostMenu>
		{
			friend class jgl::Singleton_widget<HostMenu>;

		private:
			fun::Widget::Overload::Frame* _background;

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
				jgl::Vector2Int username_label_size = jgl::Vector2Int((_area.x - space * 5) / 2, 50);
				jgl::Vector2Int username_label_pos = jgl::Vector2Int(space * 2, space * 2);

				for (jgl::Size_t i = 0; i < 4; i++)
				{
					jgl::Vector2Int tmp_pos = username_label_pos + jgl::Vector2Int(username_label_size.x + space, _area.y - username_label_size.y - space * 4) * jgl::Vector2Int(i % 2, i / 2);
					_username_label[i]->set_geometry(tmp_pos, username_label_size);
					_kick_button[i]->set_geometry(tmp_pos + jgl::Vector2Int(username_label_size.x - kick_button_size.x, 0), kick_button_size);
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

			HostMenu(jgl::Widget* p_parent) : Menu(p_parent)
			{
				_background = new fun::Widget::Overload::Frame(this);
				_background->activate();

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

			}

			void on_unfocus()
			{
				
			}
		};
	}
}