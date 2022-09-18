#include "widget/Menu/fun_main_menu.h"

namespace fun
{
	namespace Menu
	{
		void Main::_render()
		{

		}

		void Main::_on_geometry_change()
		{
			jgl::Vector2Int logo_size = jgl::Vector2Int(500, 320);
			jgl::Vector2Int entry_size = jgl::Vector2Int(500, 70);
			jgl::Vector2Int label_size = jgl::Vector2Int(250, 40);
			jgl::Vector2Int button_size = jgl::Vector2Int((entry_size.x - 10) / 2, entry_size.y / 3 * 2);

			jgl::Vector2Int logo_pos = jgl::Vector2Int((_area.x - logo_size.x) / 2, (_area.y - logo_size.y - 30 - entry_size.y - 30 - entry_size.y - 10 - button_size.y) / 2);
			jgl::Vector2Int username_entry_pos = logo_pos + jgl::Vector2Int(0, logo_size.y + 30);
			jgl::Vector2Int adress_entry_pos = username_entry_pos + jgl::Vector2Int(0, entry_size.y + 30);
			jgl::Vector2Int host_pos = adress_entry_pos + jgl::Vector2Int(0, entry_size.y + 10);
			jgl::Vector2Int connect_pos = host_pos + jgl::Vector2Int(button_size.x + 10, 0);

			_logo_frame->set_geometry(logo_pos, logo_size);
			_username_label->set_geometry(username_entry_pos - 20, label_size);
			_username_entry->set_geometry(username_entry_pos, entry_size);
			_adress_label->set_geometry(adress_entry_pos - 20, label_size);
			_adress_entry->set_geometry(adress_entry_pos, entry_size);
			_connect_button->set_geometry(connect_pos, button_size);
			_host_game->set_geometry(host_pos, button_size);
		}

		jgl::Bool Main::_update()
		{
			return (false);
		}

		jgl::Bool Main::_fixed_update()
		{
			return (false);
		}

		Main::Main(jgl::Widget* p_parent) : jgl::Widget(p_parent)
		{
			_logo_frame = new fun::Widget::Frame(this);
			_logo_frame->set_depth(1);
			_logo_frame->activate();

			_host_game = new fun::Widget::Button([&](jgl::Data_contener& p_param) {
					jgl::cout << "Hosting game" << jgl::endl;
				}, this);
			_host_game->set_depth(1);
			_host_game->label().set_text("Host");
			_host_game->activate();

			_username_label = new fun::Widget::TextLabel("Username :", this);
			_username_label->set_depth(3);
			_username_label->activate();

			_username_entry = new fun::Widget::TextEntry("", this);
			_username_entry->set_depth(1);
			_username_entry->activate();

			_adress_label = new fun::Widget::TextLabel("Server adress :", this);
			_adress_label->set_depth(3);
			_adress_label->activate();

			_adress_entry = new fun::Widget::TextEntry("", this);
			_adress_entry->set_depth(1);
			_adress_entry->activate();

			_connect_button = new fun::Widget::Button([&](jgl::Data_contener& p_param) {
					jgl::cout << "Connecting to game " << _adress_entry->label().text() << jgl::endl;
				}, this);
			_connect_button->set_depth(1);
			_connect_button->label().set_text("Connect");
			_connect_button->activate();
		}
	}
}