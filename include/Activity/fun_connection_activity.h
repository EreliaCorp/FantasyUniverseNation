#pragma once

#include "jgl.h"

#include "widget/manager/fun_activity_manager.h"
#include "structure/fun_context.h"
#include "Utils/fun_network.h"
#include "Utils/fun_event_manager.h"

namespace fun
{
	namespace Activity
	{
		class Connection : public jgl::Abstract_activity
		{
		private:
			enum class State
			{
				CheckConnection,
				ConnectionFailed,
				ConnectionAccepted,
				Completed
			};
			jgl::String to_string(State p_state)
			{
				switch (p_state)
				{
				case (State::CheckConnection):
					return ("CheckConnection");
				case (State::ConnectionFailed):
					return ("ConnectionFailed");
				case (State::ConnectionAccepted):
					return ("ConnectionAccepted");
				case (State::Completed):
					return ("Completed");
				default:
					return ("Undefined");
				}
			}
			State _state;
			jgl::Timer _timeoutTimer = jgl::Timer(3000);

			void _set_state(State p_state)
			{
				if (_state == p_state)
				{
					THROW_INFORMATION(jgl::String(__CLASS__) + " state initialize to " + to_string(_state));
				}
				else
				{
					THROW_INFORMATION(jgl::String("Setting up ") + __CLASS__ + " state from " + to_string(_state) + " to " + to_string(p_state));
				}
				_state = p_state;
			}

		public:
			void execute()
			{
				switch (_state)
				{
				case State::CheckConnection:
				{
					if (fun::Network::ClientManager::instance() == nullptr ||
						fun::Network::ClientManager::instance()->client() == nullptr ||
						fun::Network::ClientManager::instance()->client()->connection() == nullptr)
					{
						_set_state(State::ConnectionFailed);
						return;
					}
					if (fun::Network::ClientManager::instance()->client()->connection()->state() == fun::Network::Connection::State::Accepted)
					{
						_set_state(State::ConnectionAccepted);
					}
					else if (_timeoutTimer.timeout() == jgl::Timer::State::Timeout)
					{
						_set_state(State::ConnectionFailed);
					}
					break;
				}
				case State::ConnectionFailed:
				{
					fun::Network::ClientManager::instance()->desactivate();
					fun::Network::ClientManager::instance()->client()->disconnect();
					fun::Publisher::notify(fun::Event::GoMainMenu);
					_set_state(State::Completed);
					break;
				}
				case State::ConnectionAccepted:
				{
					fun::Publisher::notify(fun::Event::JoinRoom);
					fun::Publisher::notify(fun::Event::GoLobbyMenu);
					_set_state(State::Completed);
					break;
				}
				case State::Completed:
				{
					fun::ActivityManager::instance()->unsubscribe_activity(this);
					break;
				}
				}
			}
			void on_transition()
			{
				_timeoutTimer.start();
				_set_state(State::CheckConnection);
			}
		};
	}
}