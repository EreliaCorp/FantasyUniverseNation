#pragma once

#include "jgl.h"

#include "structure/fun_context.h"

namespace fun
{
	namespace Activity
	{
		class LoadProgram : public jgl::Abstract_activity
		{
		private:
			enum class State
			{
				LoadingActivities,
				ClearingContext,
				Completed
			};
			jgl::String to_string(State p_state)
			{
				switch (p_state)
				{
				case (State::LoadingActivities):
					return ("LoadingActivities");
				case (State::ClearingContext):
					return ("ClearingContext");
				case (State::Completed):
					return ("Completed");
				default:
					return ("Undefined");
				}
			}
			State _state;

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
				case State::LoadingActivities:
				{
					_set_state(State::ClearingContext);
					break;
				}
				case State::ClearingContext:
				{
					fun::Structure::Context::instance()->clear();
					_set_state(State::Completed);
					break;
				}
				case State::Completed:
				{
					fun::Publisher::notify(fun::Event::GoMainMenu);
					fun::ActivityManager::instance()->unsubscribe_activity(this);
					break;
				}
				}
			}
			void on_transition()
			{
				_set_state(State::LoadingActivities);
			}
		};
	}
}