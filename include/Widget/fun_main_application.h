#pragma once

#include "jgl.h"

#include "widget/Abstract/fun_menu.h"
#include "Widget/Manager/fun_activity_manager.h"
#include "Activity/fun_load_program_activity.h"

namespace fun
{
	class MainApplication : public jgl::Widget
	{
	private:
		fun::Abstract::Menu* _active_menu;

		void _render()
		{

		}
		void _on_geometry_change()
		{
			fun::Menu::MainMenu::instance()->set_geometry(0, _area);
			fun::Menu::LobbyMenu::instance()->set_geometry(0, _area);
			fun::Menu::GameMenu::instance()->set_geometry(0, _area);
		}

		jgl::Bool _update()
		{
			return (false);
		}
		jgl::Bool _fixed_update()
		{
			return (false);
		}

	public:
		MainApplication(jgl::Widget* p_parent) : jgl::Widget(p_parent),
			_active_menu(nullptr)
		{
			fun::Structure::Context::instanciate();

			fun::Menu::MainMenu::instanciate(this);
			fun::Menu::MainMenu::instance()->activate();

			fun::Menu::LobbyMenu::instanciate(this);
			fun::Menu::LobbyMenu::instance()->activate();

			fun::Menu::GameMenu::instanciate(this);
			fun::Menu::GameMenu::instance()->activate();

			fun::ActivityManager::instanciate(nullptr);
			fun::ActivityManager::instance()->activate();

			fun::ActivityManager::instance()->subscribe_activity(fun::Event::LoadProgram, new fun::Activity::LoadProgram());

			fun::Publisher::subscribe(fun::Event::GoMainMenu, [&]() {
					jgl::cout << "Activating menu [fun::Menu::MainMenu]" << jgl::endl;
					active_menu(fun::Menu::MainMenu::instance());
				});
			fun::Publisher::subscribe(fun::Event::GoLobbyMenu, [&]() {
					jgl::cout << "Activating menu [fun::Menu::LobbyMenu]" << jgl::endl;
					active_menu(fun::Menu::LobbyMenu::instance());
				});
			fun::Publisher::subscribe(fun::Event::GoGameMenu, [&]() {
					jgl::cout << "Activating menu [fun::Menu::GameMenu]" << jgl::endl;
					active_menu(fun::Menu::GameMenu::instance());
				});
			fun::Publisher::notify(fun::Event::LoadProgram);


		}

		void active_menu(fun::Abstract::Menu* p_active_menu)
		{
			if (_active_menu != nullptr)
			{
				_active_menu->on_unfocus();
				_active_menu->desactivate();
			}
			_active_menu = p_active_menu;
			if (_active_menu != nullptr)
			{
				_active_menu->on_focus();
				_active_menu->activate();
			}
		}
	};
}