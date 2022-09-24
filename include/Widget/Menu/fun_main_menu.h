#pragma once

#include "widget/abstract/fun_menu.h"

namespace fun
{
	namespace Menu
	{
		class MainMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<MainMenu>
		{
		public:
			friend class jgl::Singleton_widget<MainMenu>;

		private:
			fun::Widget::Overload::Frame* _background;

			fun::Widget::Overload::TextLabel* _username_label;
			fun::Widget::Overload::TextEntry* _username_entry;

			fun::Widget::Overload::TextLabel* _address_label;
			fun::Widget::Overload::TextEntry* _address_entry;

			fun::Widget::Overload::Button* _connect_button;
			fun::Widget::Overload::Button* _host_button;

			void _render()
			{

			}

			void _on_geometry_change()
			{
				_background->set_geometry(0, _area);

				jgl::Float space = 10;
				jgl::Vector2Int label_anchor_delta = jgl::Vector2Int(15, 15);
				jgl::Vector2Int label_size = jgl::Vector2Int(150, 30);

				jgl::Vector2Int username_pos = jgl::Vector2Int(50, 50);
				jgl::Vector2Int username_size = jgl::Vector2Int(300, 50);

				jgl::Vector2Int address_pos = jgl::Vector2Int(50, username_pos.y + username_size.y + space + label_anchor_delta.y);
				jgl::Vector2Int address_size = jgl::Vector2Int(username_size.x, username_size.y);

				jgl::Vector2Int connect_pos = jgl::Vector2Int(50, address_pos.y + address_size.y + space);
				jgl::Vector2Int button_size = jgl::Vector2Int((username_size.x - 10) / 2, username_size.y);

				jgl::Vector2Int used_size = jgl::Vector2Int(
					label_anchor_delta.x + username_size.x + label_anchor_delta.x,
					label_anchor_delta.y + username_size.y + space + label_anchor_delta.y + address_size.y + space + label_anchor_delta.y + space + button_size.y
				);

				jgl::Vector2 delta_pos = (_area - used_size) / 2;

				_username_entry->set_geometry(delta_pos + username_pos, username_size);
				_username_label->set_geometry(delta_pos + username_pos - label_anchor_delta, label_size);
				_address_entry->set_geometry(delta_pos + address_pos, address_size);
				_address_label->set_geometry(delta_pos + address_pos - label_anchor_delta, label_size);

				_connect_button->set_geometry(delta_pos + connect_pos, button_size);
				_host_button->set_geometry(delta_pos + connect_pos + jgl::Vector2Int(button_size.x + 10, 0), button_size);
			}

			jgl::Bool _update()
			{
				return (false);
			}

			jgl::Bool _fixed_update()
			{
				return (false);
			}

			MainMenu(jgl::Widget* p_parent) : Menu(p_parent)
			{
				_background = new fun::Widget::Overload::Frame(this);
				_background->activate();

				_username_label = new fun::Widget::Overload::TextLabel("Username :", _background);
				_username_label->set_depth(_depth + 4);
				_username_label->activate();

				_username_entry = new fun::Widget::Overload::TextEntry("Hyarius", _background);
				_username_entry->set_depth(_depth + 2);
				_username_entry->activate();

				_address_label = new fun::Widget::Overload::TextLabel("Address :", _background);
				_address_label->set_depth(_depth + 4);
				_address_label->activate();

				_address_entry = new fun::Widget::Overload::TextEntry("localhost", _background);
				_address_entry->set_depth(_depth + 2);
				_address_entry->activate();

				_connect_button = new fun::Widget::Overload::Button("Connect", [&](jgl::Data_contener& p_param) {
						if (_username_entry->label().text() != "" && _address_entry->label().text() != "")
						{
							fun::Structure::Context::instance()->username = _username_entry->label().text();
							fun::Structure::Context::instance()->address = _address_entry->label().text();
							fun::Publisher::notify(fun::Event::StartClient);
						}
					}, _background);
				_connect_button->set_depth(_depth + 2);
				_connect_button->activate();

				_host_button = new fun::Widget::Overload::Button("Host", [&](jgl::Data_contener& p_param) {
						fun::Publisher::notify(fun::Event::GoHostMenu);
					}, _background);
				_host_button->set_depth(_depth + 2);
				_host_button->activate();
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