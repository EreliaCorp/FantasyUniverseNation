#pragma once

#include "jgl.h"

#include "widget/Abstract/fun_menu.h"
#include "Widget/Manager/fun_activity_manager.h"
#include "Activity/fun_load_program_activity.h"

#include "widget/menu/fun_main_menu.h"
#include "widget/menu/fun_player_lobby_menu.h"
#include "widget/menu/fun_host_lobby_menu.h"
#include "widget/menu/fun_player_game_menu.h"
#include "widget/menu/fun_host_game_menu.h"

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
			fun::Menu::PlayerLobbyMenu::instance()->set_geometry(0, _area);
			fun::Menu::HostLobbyMenu::instance()->set_geometry(0, _area);
			fun::Menu::PlayerGameMenu::instance()->set_geometry(0, _area);
			fun::Menu::HostGameMenu::instance()->set_geometry(0, _area);
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

			fun::Menu::PlayerLobbyMenu::instanciate(this);

			fun::Menu::HostLobbyMenu::instanciate(this);

			fun::Menu::PlayerGameMenu::instanciate(this);

			fun::Menu::HostGameMenu::instanciate(this);

			fun::Publisher::subscribe(fun::Event::GoMainMenu, [&]() {
				jgl::cout << "Activating menu [fun::Menu::MainMenu]" << jgl::endl;
				active_menu(fun::Menu::MainMenu::instance());
				});

			fun::Publisher::subscribe(fun::Event::GoPlayerLobbyMenu, [&]() {
				jgl::cout << "Activating menu [fun::Menu::PlayerLobbyMenu]" << jgl::endl;
				active_menu(fun::Menu::PlayerLobbyMenu::instance());
				});

			fun::Publisher::subscribe(fun::Event::GoHostLobbyMenu, [&]() {
				jgl::cout << "Activating menu [fun::Menu::HostLobbyMenu]" << jgl::endl;
				active_menu(fun::Menu::HostLobbyMenu::instance());
					fun::Publisher::notify(fun::Event::StartServer);
				});

			fun::Publisher::subscribe(fun::Event::GoPlayerGameMenu, [&]() {
				jgl::cout << "Activating menu [fun::Menu::PlayerGameMenu]" << jgl::endl;
				active_menu(fun::Menu::PlayerGameMenu::instance());
				});

			fun::Publisher::subscribe(fun::Event::GoHostGameMenu, [&]() {
				jgl::cout << "Activating menu [fun::Menu::HostGameMenu]" << jgl::endl;
				active_menu(fun::Menu::HostGameMenu::instance());
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