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
			virtual void _on_server_instanciation() = 0;
			virtual void _on_client_instanciation() = 0;

		public:
			virtual void on_focus() = 0;
			virtual void on_unfocus() = 0;

			Menu(jgl::Widget *p_parent) : jgl::Widget(p_parent)
			{
				fun::Publisher::subscribe(fun::Event::OnServerInstanciation, [&]() {
						_on_server_instanciation();
					});
				fun::Publisher::subscribe(fun::Event::OnClientInstanciation, [&]() {
						_on_client_instanciation();
					});
			}
		};
	}
}