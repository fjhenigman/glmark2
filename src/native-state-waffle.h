/*
 * Copyright 2015 Google Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */
#ifndef GLMARK2_NATIVE_STATE_WAFFLE_H_
#define GLMARK2_NATIVE_STATE_WAFFLE_H_

#include "native-state.h"
#define WAFFLE_API_VERSION 0x0106
#include <waffle.h>

class NativeStateWaffle : public NativeState
{
public:
    NativeStateWaffle() : wdpy_(0), wwin_(0), properties_() {}
    ~NativeStateWaffle();

    bool init_display();
    void* display();
    bool create_window(WindowProperties const& properties);
    void* window(WindowProperties& properties);
    void visible(bool v);
    bool should_quit();
    void flip() { }

private:
    /** The waffle display associated with this canvas. */
    waffle_display* wdpy_;
    /** The waffle window associated with this canvas. */
    waffle_window* wwin_;
    WindowProperties properties_;
};

#endif /* GLMARK2_NATIVE_STATE_WAFFLE_H_ */
