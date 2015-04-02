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
#ifndef GLMARK2_GL_STATE_WAFFLE_H_
#define GLMARK2_GL_STATE_WAFFLE_H_

#include <vector>
#include <EGL/egl.h>
#include <waffle.h>
#include "gl-state.h"
#include "gl-visual-config.h"

class GLStateWaffle : public GLState
{
    void* native_display_;
    void* native_window_;
    waffle_display* waffle_display_;
    waffle_config* waffle_config_;
    waffle_context* waffle_context_;
    waffle_window* waffle_surface_;
    GLVisualConfig requested_visual_config_;
    bool gotValidDisplay();
    bool gotValidConfig();
    bool gotValidSurface();
    bool gotValidContext();
    void get_glvisualconfig(waffle_config* config, GLVisualConfig& visual_config);
    EGLConfig select_best_config(std::vector<EGLConfig>& configs);
public:
    GLStateWaffle() :
        native_display_(0),
        native_window_(0),
        waffle_display_(0),
        waffle_config_(0),
        waffle_context_(0),
        waffle_surface_(0) {}

    bool init_display(void* native_display, GLVisualConfig& config_pref);
    bool init_surface(void* native_window);
    void init_gl_extensions();
    bool valid();
    bool reset();
    void swap();
    // Performs a config search, returning a native visual ID on success
    bool gotNativeConfig(intptr_t& vid);
    void getVisualConfig(GLVisualConfig& vc);
};

#endif // GLMARK2_GL_STATE_WAFFLE_H_
