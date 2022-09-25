#pragma once

#include "jgl.h"

#include "widget/Abstract/fun_menu.h"
#include "Widget/Manager/fun_activity_manager.h"
#include "Activity/fun_load_program_activity.h"

#include "widget/menu/fun_main_menu.h"
#include "widget/menu/fun_lobby_menu.h"
#include "widget/menu/fun_host_menu.h"
#include "widget/menu/fun_game_menu.h"

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
			fun::Menu::HostMenu::instance()->set_geometry(0, _area);
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
			fun::ActivityManager::instanciate(nullptr);
			fun::ActivityManager::instance()->activate();

			fun::ActivityManager::instance()->subscribe_activity(fun::Event::LoadProgram, new fun::Activity::LoadProgram());

			fun::Structure::Context::instanciate();

			fun::Menu::MainMenu::instanciate(this);

			fun::Menu::LobbyMenu::instanciate(this);

			fun::Menu::HostMenu::instanciate(this);

			fun::Menu::GameMenu::instanciate(this);

			fun::Publisher::subscribe(fun::Event::GoMainMenu, [&]() {
					jgl::cout << "Activating menu [fun::Menu::MainMenu]" << jgl::endl;
					active_menu(fun::Menu::MainMenu::instance());
				});

			fun::Publisher::subscribe(fun::Event::GoLobbyMenu, [&]() {
					jgl::cout << "Activating menu [fun::Menu::LobbyMenu]" << jgl::endl;
					active_menu(fun::Menu::LobbyMenu::instance());
				});

			fun::Publisher::subscribe(fun::Event::GoHostMenu, [&]() {
					jgl::cout << "Activating menu [fun::Menu::HostMenu]" << jgl::endl;
					active_menu(fun::Menu::HostMenu::instance());
					fun::Publisher::notify(fun::Event::StartServer);
				});

			fun::Publisher::subscribe(fun::Event::GoGameMenu, [&]() {
					jgl::cout << "Activating menu [fun::Menu::GameMenu]" << jgl::endl;
					active_menu(fun::Menu::GameMenu::instance());
				});

			fun::Publisher::subscribe(fun::Event::StartClient, [&]() {
					jgl::cout << "Starting the client manager" << jgl::endl;
					try
					{
						if (fun::Network::ClientManager::instance() != nullptr)
						{
							_remove_children(fun::Network::ClientManager::instance());
							fun::Network::ClientManager::release();
						}

						fun::Network::ClientManager::instanciate(this);

						fun::Network::ClientManager::instance()->activate();

						fun::Network::ClientManager::instance()->start(fun::Structure::Context::instance()->address, SERVER_PORT);

						fun::Publisher::notify(fun::Event::OnClientInstanciation);
						fun::Publisher::notify(fun::Event::CheckConnection);
					}
					catch (...)
					{
						fun::Publisher::notify(fun::Event::GoMainMenu);
					}
				});

			fun::Publisher::subscribe(fun::Event::StartServer, [&]() {
					jgl::cout << "Starting the server manager" << jgl::endl;
					try
					{
						if (fun::Network::ServerManager::instance() == nullptr)
							fun::Network::ServerManager::instanciate(this);

						fun::Network::ServerManager::instance()->activate();

						fun::Network::ServerManager::instance()->start(SERVER_PORT);

						fun::Publisher::notify(fun::Event::OnServerInstanciation);
					}
					catch (...)
					{
						fun::Publisher::notify(fun::Event::GoMainMenu);
					}
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