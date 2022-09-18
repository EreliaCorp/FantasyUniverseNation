#pragma once

#include "jgl.h"

#include "widget/menu/fun_main_menu.h"

namespace fun
{
	class MainApplication : public jgl::Singleton_widget<MainApplication>, public jgl::Widget
	{
		friend class jgl::Singleton_widget<MainApplication>;

	protected:
		fun::Menu::Main* _main;

		MainApplication(jgl::Widget* p_parent);

		void _render();
		void _on_geometry_change();

		jgl::Bool _update();
		jgl::Bool _fixed_update();

	public:
		void start_manager();
	};
}