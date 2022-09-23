#pragma once

#include "jgl.h"

namespace fun
{
	namespace Structure
	{
		struct AccountData
		{
			jgl::Long id = 0;
			jgl::String username = "";
		};

		struct GameRoomData
		{
			static const jgl::Size_t C_MAX_PLAYER = 4u;

			AccountData players[C_MAX_PLAYER] = {
				{},{},{},{}
			};
		};

		struct Context : public jgl::Singleton<Context>
		{
			AccountData master;
			GameRoomData gameRoom;

			void clear()
			{
				THROW_INFORMATION("Clearing global context");
				master = AccountData();
				gameRoom = GameRoomData();
			}
		};
	}
}