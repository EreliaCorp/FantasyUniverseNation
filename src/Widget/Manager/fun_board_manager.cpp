#include "widget/manager/fun_board_manager.h"


namespace fun
{
	namespace Manager
	{
		void BoardManager::_render()
		{

		}

		void BoardManager::_on_geometry_change()
		{
			jgl::Float space = 5;

			_board_renderer->set_geometry(space, _area - space * 2);
		}

		jgl::Bool BoardManager::_update()
		{
			return (false);
		}

		jgl::Bool BoardManager::_fixed_update()
		{
			return (false);
		}

		BoardManager::BoardManager(jgl::Widget* p_parent) : jgl::Widget(p_parent)
		{
			_board_renderer = new fun::Widget::BoardRenderer(this);
			_board_renderer->set_depth(1);
			_board_renderer->activate();
		}
	}
}