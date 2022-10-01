#pragma once

#include "jgl.h"

namespace fun
{
	enum class Event
	{
		LoadProgram,
		ClearContextGlobal,
		GoMainMenu,
		GoPlayerLobbyMenu,
		GoHostLobbyMenu,
		GoPlayerGameMenu,
		GoHostGameMenu,
		StartServer,
		OnServerInstanciation,
		StartClient,
		OnClientInstanciation,
		CheckConnection,
		JoinRoom,
		OnBoardEdition
	};

	class Publisher : public jgl::Singleton<jgl::Publisher<Event>>
	{
		friend jgl::Singleton<jgl::Publisher<Event>>;

		static jgl::String to_string(fun::Event p_event)
		{
			switch (p_event)
			{
			case fun::Event::LoadProgram:
				return ("LoadProgram");
			case fun::Event::ClearContextGlobal:
				return ("ClearContextGlobal");
			case fun::Event::GoMainMenu:
				return ("GoMainMenu");
			case fun::Event::GoPlayerLobbyMenu:
				return ("GoPlayerLobbyMenu");
			case fun::Event::GoHostLobbyMenu:
				return ("GoHostLobbyMenu");
			case fun::Event::GoPlayerGameMenu:
				return ("GoPlayerGameMenu");
			case fun::Event::GoHostGameMenu:
				return ("GoHostGameMenu");
			case fun::Event::StartServer:
				return ("StartServer");
			case fun::Event::StartClient:
				return ("StartClient");
			case fun::Event::CheckConnection:
				return ("CheckConnection");
			case fun::Event::JoinRoom:
				return ("JoinRoom");
			case fun::Event::OnBoardEdition:
				return ("OnBoardEdition");
			default :
				return ("Default event");
				break;
			}
			return ("Unknow");
		}

	public:
		static void notify(Event p_event)
		{
			THROW_INFORMATION("Notify event " + to_string(p_event));
			instance()->notify(p_event);
		}
		static void subscribe(Event p_event, jgl::Publisher<Event>::Activity p_funct)
		{
			THROW_INFORMATION("Activity linked to event " + to_string(p_event));
			instance()->subscribe(p_event, p_funct);

		}
	};
}