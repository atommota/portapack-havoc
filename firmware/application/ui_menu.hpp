/*
 * Copyright (C) 2014 Jared Boone, ShareBrained Technology, Inc.
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __UI_MENU_H__
#define __UI_MENU_H__

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_painter.hpp"
#include "bitmap.hpp"
#include "signal.hpp"

#include <cstddef>
#include <string>
#include <functional>

#define MENU_MAX 11

namespace ui {

struct MenuItem {
	std::string text;
	ui::Color color;
	std::function<void(void)> on_select;

	// TODO: Prevent default-constructed MenuItems.
	// I managed to construct a menu with three extra, unspecified menu items
	// in the array that were default constructed...
};

class MenuItemView : public Widget {
public:
	MenuItemView(
		MenuItem item
	) : item(item)
	{
	}

	void paint(Painter& painter) override;

	void select();
	void highlight();
	void unhighlight();

private:
	const MenuItem item;
};

class MenuView : public View {
public:
	std::function<void(void)> on_left;

	MenuView();
	~MenuView();

	void add_item(const MenuItem item);

	template<size_t N>
	void add_items(const std::array<MenuItem, N>& items) {
		for (const auto& item : items) {
			add_item(item);
		}
	}

	void set_parent_rect(const Rect new_parent_rect) override;
	
	MenuItemView* item_view(size_t index) const;

	size_t highlighted() const;
	bool set_highlighted(const size_t new_value);

	void on_focus() override;
	void on_blur() override;
	bool on_key(const KeyEvent event) override;
	bool on_encoder(const EncoderEvent event) override;
	//bool on_touch(const TouchEvent event) override;

private:
	void update_items();
	void on_tick_second();
	
	SignalToken signal_token_tick_second;
	
	Image arrow_more {
		{ 216, 320 - 16 - 24, 16, 16 },
		&bitmap_more,
		Color::white(),
		Color::black()
	};

	bool blink_ = false;
	bool more_ = false;
	size_t highlighted_ { 0 };
	size_t offset_ { 0 };
};

} /* namespace ui */

#endif/*__UI_MENU_H__*/
