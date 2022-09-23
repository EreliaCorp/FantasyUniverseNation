#pragma once

#include "jgl.h"

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

		public:
			virtual void on_focus() = 0;
			virtual void on_unfocus() = 0;

			Menu(jgl::Widget *p_parent) : jgl::Widget(p_parent)
			{

			}
		};
	}
}