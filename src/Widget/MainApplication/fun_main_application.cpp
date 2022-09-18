#include "widget/mainapplication/fun_main_application.h"

#include "widget/manager/fun_board_manager.h"
#include "widget/manager/fun_player_manager.h"

#include "Utils/fun_network.h"

namespace fun
{
	void MainApplication::_render()
	{

	}

	void MainApplication::_on_geometry_change()
	{
		_main->set_geometry(0, _area);
	}

	jgl::Bool MainApplication::_update()
	{
		return (false);
	}

	jgl::Bool MainApplication::_fixed_update()
	{
		return (false);
	}

	void MainApplication::start_manager()
	{

	}

	MainApplication::MainApplication(jgl::Widget* p_parent) : jgl::Widget(p_parent)
	{
		_main = new fun::Menu::Main(this);
		_main->activate();
	}
}