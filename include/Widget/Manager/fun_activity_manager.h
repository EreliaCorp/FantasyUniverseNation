#pragma once

#include "jgl.h"
#include "utils/fun_event_manager.h"
#include "Widget/Abstract/fun_manager.h"

namespace fun
{
	class ActivityManager : public jgl::Singleton_widget<ActivityManager>, public Manager
	{
		friend class jgl::Singleton_widget<ActivityManager>;

	private:
		jgl::Array<jgl::Abstract_activity*> _active_activities;

		jgl::Bool _update()
		{
			for (jgl::Size_t i = 0; i < _active_activities.size(); i++)
			{
				_active_activities[i]->execute();
			}
			return (false);
		}

		ActivityManager(jgl::Widget* p_parent) : Manager(p_parent)
		{
			fun::Publisher::instanciate();
		}

	public:

		void unsubscribe_activity(jgl::Abstract_activity* p_activity)
		{
			auto tmp = _active_activities.find(p_activity);

			if (tmp != _active_activities.end())
			{
				_active_activities.erase(tmp);
			}
			else
			{
				THROW_EXCEPTION(jgl::Error_level::Warning, 1, "Activity to delete wasn't active");
			}
		}

		void subscribe_activity(fun::Event p_event, jgl::Abstract_activity* p_activity)
		{
			fun::Publisher::subscribe(p_event, [=]() {
					_active_activities.push_back(p_activity);
					p_activity->on_transition();
				});
		}
	};
}