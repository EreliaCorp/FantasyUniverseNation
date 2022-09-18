#pragma once

#include "jgl.h"

namespace fun
{
	enum class ServerMessage
	{

	};

	using Connection = jgl::Connection<ServerMessage>;
	using Message = jgl::Message<ServerMessage>;
	using Server = jgl::Server<ServerMessage>;
	using Client = jgl::Client<ServerMessage>;
	using ServerManager = jgl::Server_manager<ServerMessage>;
	using ClientManager = jgl::Client_manager<ServerMessage>;
}
#define SERVER_ACTIVITY(p_msg_type) woe::Server_manager::instance()->add_activity(p_msg_type, [&](woe::Connection* p_client, woe::Message& p_msg, jgl::Data_contener& p_param)
#define CLIENT_ACTIVITY(p_msg_type) woe::Client_manager::instance()->add_activity(p_msg_type, [&](woe::Message& p_msg, jgl::Data_contener& p_param)