/*
 * Copyright (C) 2015 Jared Boone, ShareBrained Technology, Inc.
 * Copyright (C) 2016 Furrtek
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

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_painter.hpp"
#include "ui_menu.hpp"
#include "ui_navigation.hpp"

namespace ui {

class FrequencySaveView : public View {
public:
	FrequencySaveView(NavigationView& nav, const rf::Frequency value);
	//~FrequencySaveView();
	
	void focus() override;

	std::string title() const override { return "Save frequency"; };

private:
	Button button_exit {
		{ 72, 264, 96, 32 },
		"Exit"
	};	
};

class FreqManView : public View {
public:
	FreqManView(NavigationView& nav);
	//~FreqManView();
	
	void focus() override;

	std::string title() const override { return "Freq. manager"; };

private:
	std::array<Text, 10> text_list;

	Button button_exit {
		{ 72, 264, 96, 32 },
		"Exit"
	};
};

} /* namespace ui */
