#pragma once

#include "jgl.h"

namespace fun
{
	namespace Structure
	{
		struct Context : public jgl::Singleton<Context>
		{
			jgl::String username;
			jgl::String address;

			void clear()
			{
				THROW_INFORMATION("Clearing global context");

				username = "";
				address = "";
			}
		};
	}
}