#pragma once

#include "Utils/fun_network.h"
#include "widget/abstract/fun_menu.h"

namespace fun
{
	namespace Menu
	{
		class LobbyMenu : public fun::Abstract::Menu, public jgl::Singleton_widget<LobbyMenu>
		{
			friend class jgl::Singleton_widget<LobbyMenu>;

		private:
			jgl::Timer _connection_timer = jgl::Timer(3000);
			jgl::Bool _connection_accepted = false;

			void _render()
			{

			}

			void _on_geometry_change()
			{

			}

			jgl::Bool _update()
			{
				if (fun::Network::ClientManager::instance() == nullptr)
					return false;

				if (fun::Network::ClientManager::instance()->client()->connection()->state() == fun::Network::Connection::State::Accepted)
				{
					_connection_accepted = true;
				}
				else if (_connection_accepted == false && _connection_timer.timeout() == jgl::Timer::State::Timeout)
				{
					fun::Publisher::notify(fun::Event::GoMainMenu);
				}
				return (false);
			}

			jgl::Bool _fixed_update()
			{
				return (false);
			}

			LobbyMenu(jgl::Widget* p_parent) : Menu(p_parent)
			{

			}

		public:

			void on_focus()
			{
				_connection_timer.start();
				_connection_accepted = false;
			}

			void on_unfocus()
			{

			}
		};
	}
}