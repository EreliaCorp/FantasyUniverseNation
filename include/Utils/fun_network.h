#pragma once

#include "jgl.h"

namespace fun
{
	namespace Network
	{
		enum class ServerMessage
		{
			PlayerJoinRoom,
			GameRoomData
		};

		using Connection = jgl::Connection<ServerMessage>;
		using Message = jgl::Message<ServerMessage>;
		using Server = jgl::Server<ServerMessage>;
		using Client = jgl::Client<ServerMessage>;
		using ServerManager = jgl::Server_manager<ServerMessage>;
		using ClientManager = jgl::Client_manager<ServerMessage>;
	}
}
#define SERVER_PORT 25200
#define SERVER_ACTIVITY(p_msg_type) fun::Network::ServerManager::instance()->add_activity(p_msg_type, [&](fun::Network::Connection* p_client, fun::Network::Message& p_msg, jgl::Data_contener& p_param)
#define CLIENT_ACTIVITY(p_msg_type) fun::Network::ClientManager::instance()->add_activity(p_msg_type, [&](fun::Network::Message& p_msg, jgl::Data_contener& p_param)