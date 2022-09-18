#pragma once

#include "jgl.h"

#include "widget/widget/fun_frame.h"
#include "widget/widget/fun_text_entry.h"
#include "widget/widget/fun_text_label.h"
#include "widget/widget/fun_button.h"

namespace fun
{
	namespace Menu
	{
		class Main : public jgl::Widget
		{
		private:
			fun::Widget::Frame* _logo_frame;
			fun::Widget::Button* _host_game;

			fun::Widget::TextLabel* _username_label;
			fun::Widget::TextEntry* _username_entry;

			fun::Widget::TextLabel* _adress_label;
			fun::Widget::TextEntry* _adress_entry;

			fun::Widget::Button* _connect_button;

			void _render();
			void _on_geometry_change();

			jgl::Bool _update();
			jgl::Bool _fixed_update();

		public:
			Main(jgl::Widget* p_parent);
		};
	}
}