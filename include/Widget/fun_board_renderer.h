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
			jgl::Vector2 _card_unit;

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

				_card_unit = jgl::Vector2(_area) / fun::Structure::Board::C_SIZE;

				for (jgl::Size_t i = 0; i < _card_renderers.size(); i++)
				{
					if (_card_renderers[i]->card() != nullptr)
					{
						_card_renderers[i]->set_geometry(_card_unit * _card_renderers[i]->card()->pos, _card_area);
					}
				}
			}

			jgl::Bool _update()
			{

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

			jgl::Array<fun::Widget::CardRenderer*>& card_renderers() { return (_card_renderers); }

			jgl::Vector2 card_unit() { return (_card_unit); }

			fun::Widget::CardRenderer* selected_card()
			{
				fun::Widget::CardRenderer* result = nullptr;

				for (jgl::Size_t i = 0; i < _card_renderers.size(); i++) 
				{
					if (_card_renderers[i]->is_pointed() == true && (result == nullptr || _card_renderers[i]->depth() > result->depth()))
					{
						result = _card_renderers[i];
					}
				}

				return (result);
			}

			void update_board()
			{
				for (jgl::Size_t i = 0; i < fun::Structure::Context::instance()->board.played_cards.size(); i++)
				{
					if (_card_renderer_pool.size() == 0)
					{
						fun::Widget::CardRenderer* new_card = new fun::Widget::CardRenderer(this);
						_card_renderer_pool.push_back(new_card);
					}
					if (_card_renderers.size() <= i)
					{
						fun::Widget::CardRenderer* tmp_card = _card_renderer_pool.last();
						_card_renderer_pool.pop_back();
						_card_renderers.push_back(tmp_card);
					}

					_card_renderers[i]->set_card(&(fun::Structure::Context::instance()->board.played_cards[i]));
					_card_renderers[i]->set_depth(fun::Structure::Context::instance()->board.played_cards[i].level * 10);
					_card_renderers[i]->activate();
				}

				for (jgl::Size_t i = fun::Structure::Context::instance()->board.played_cards.size(); i < _card_renderers.size(); i++)
				{
					_card_renderers[i]->desactivate();
				}

				_on_geometry_change();
			}
		};
	}
}