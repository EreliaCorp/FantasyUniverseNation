#pragma once

#include "jgl.h"

#include "Utils/fun_event_manager.h"

#include "widget/Overload/fun_button.h"
#include "widget/Overload/fun_frame.h"
#include "widget/Overload/fun_text_label.h"
#include "widget/Overload/fun_text_entry.h"

namespace fun
{
	namespace Abstract
	{
		class Menu : public jgl::Widget
		{
		private:
			jgl::Bool _server_instanciation_performed = false;
			jgl::Bool _client_instanciation_performed = false;

			virtual void _on_server_instanciation() = 0;
			virtual void _on_client_instanciation() = 0;

		public:
			virtual void on_focus() = 0;
			virtual void on_unfocus() = 0;

			Menu(jgl::Widget *p_parent) : jgl::Widget(p_parent)
			{
				fun::Publisher::subscribe(fun::Event::OnServerInstanciation, [&]() {
						if (_server_instanciation_performed == false)
						{
							_on_server_instanciation();
							_server_instanciation_performed = true;
						}
					});
				fun::Publisher::subscribe(fun::Event::OnClientInstanciation, [&]() {
						if (_client_instanciation_performed == false)
						{
							_on_client_instanciation();
							_client_instanciation_performed = true;
						}
					});
			}
		};
	}
}