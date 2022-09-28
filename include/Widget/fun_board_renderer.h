#pragma once

#include "jgl.h"

#include "widget/Overload/fun_button.h"
#include "widget/Overload/fun_frame.h"
#include "widget/Overload/fun_text_label.h"
#include "widget/Overload/fun_text_entry.h"

#include "widget/fun_card_renderer.h"

#include "structure/fun_context.h"

namespace fun
{
	namespace Widget
	{
		class BoardRenderer : public jgl::Widget
		{
		private:
			fun::Widget::Overload::Frame* _board_frame;
			
			jgl::Vector2Int _card_area;

			jgl::Float _top_depth = 10;
			jgl::Vector2Int _delta_anchor;
			fun::Widget::CardRenderer* _selected_card;

			jgl::Array<fun::Widget::CardRenderer*> _card_renderers;
			jgl::Array<fun::Widget::CardRenderer*> _card_renderer_pool;

			void _render()
			{
				
			}
			void _on_geometry_change()
			{
				jgl::Float space = 10;

				_board_frame->set_geometry(space, _area - space * 2);

				_card_area = jgl::Vector2Int(_area.x / 8, _area.x / 8 * 1.4f);

				for (jgl::Size_t i = 0; i < _card_renderers.size(); i++)
				{
					_card_renderers[i]->set_geometry(jgl::Vector2Int(50 + (_card_area.x + 20) * i, 50), _card_area);
				}
			}

			jgl::Bool _update()
			{
				if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Pressed)
				{
					_selected_card = nullptr;

					for (jgl::Size_t i = 0; i < _card_renderers.size(); i++)
					{
						jgl::cout << "Comparing depth " << (_selected_card == nullptr ? -1 : _selected_card->depth()) << " vs " << _card_renderers[i]->depth() << jgl::endl;
						if (_card_renderers[i]->is_pointed() == true && (_selected_card == nullptr || _card_renderers[i]->depth() > _selected_card->depth()))
						{
							_delta_anchor = _card_renderers[i]->anchor() - jgl::Application::active_application()->mouse().pos();
							_selected_card = _card_renderers[i];
						}
					}
					if (_selected_card != nullptr)
					{
						_top_depth++;
						_selected_card->set_depth(_top_depth);
					}
				}

				if (_selected_card != nullptr)
				{
					if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Down)
					{
						_selected_card->set_geometry(jgl::Application::active_application()->mouse().pos() + _delta_anchor, _selected_card->area());
					}
				}

				return (false);
			}
			jgl::Bool _fixed_update()
			{
				return (false);
			}

		public:
			BoardRenderer(jgl::Widget* p_parent) : jgl::Widget(p_parent)
			{
				_board_frame = new fun::Widget::Overload::Frame(this);
				_board_frame->set_depth(4);
				_board_frame->box().set_color(jgl::Color(227, 177, 120), jgl::Color(176, 137, 93));
				_board_frame->activate();
			}

			void update_board()
			{
				for (jgl::Size_t i = 0; i < _card_renderers.size(); i++)
				{
					_card_renderers[i]->desactivate();
					_card_renderer_pool.push_back(_card_renderers[i]);
				}
				_card_renderers.clear();

				_top_depth = 10;

				for (jgl::Size_t i = 0; i < 4; i++)
				{
					if (_card_renderer_pool.size() == 0)
					{
						fun::Widget::CardRenderer* new_card = new fun::Widget::CardRenderer(this);
						new_card->set_depth(10);
						_card_renderer_pool.push_back(new_card);
					}

					fun::Widget::CardRenderer* tmp_card = _card_renderer_pool.last();
					tmp_card->set_geometry(jgl::Vector2Int(50 + (_card_area.x + 20) * i, 50), _card_area);
					tmp_card->set_depth(_top_depth);
					_top_depth++;
					tmp_card->activate();

					_card_renderer_pool.pop_back();
					_card_renderers.push_back(tmp_card);
				}
			}
		};
	}
}