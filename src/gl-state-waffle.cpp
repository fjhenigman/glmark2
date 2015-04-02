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
#include "gl-state-waffle.h"
#include "log.h"
#include "options.h"
#include "gl-headers.h"
#include "limits.h"
#include "gl-headers.h"
#include <iomanip>
#include <sstream>
#include <waffle_null.h>

using std::vector;
using std::string;

/*****************************
 * GLStateWaffle public methods *
 ****************************/

bool
GLStateWaffle::init_display(void* native_display, GLVisualConfig& visual_config)
{
    native_display_ = native_display;
    requested_visual_config_ = visual_config;

    return gotValidDisplay();
}

bool
GLStateWaffle::init_surface(void* native_window)
{
    native_window_ = native_window;

    return gotValidSurface();
}

void
GLStateWaffle::init_gl_extensions()
{
#if GLMARK2_USE_GLESv2
    if (GLExtensions::support("GL_OES_mapbuffer")) {
        GLExtensions::MapBuffer =
            reinterpret_cast<PFNGLMAPBUFFEROESPROC>(eglGetProcAddress("glMapBufferOES"));
        GLExtensions::UnmapBuffer =
            reinterpret_cast<PFNGLUNMAPBUFFEROESPROC>(eglGetProcAddress("glUnmapBufferOES"));
    }
#elif GLMARK2_USE_GL
    GLExtensions::MapBuffer = glMapBuffer;
    GLExtensions::UnmapBuffer = glUnmapBuffer;
#endif
}

static void
LogWaffleError(const char* msg)
{
    const struct waffle_error_info* info = waffle_error_get_info();
    Log::error("%s - %s - %s\n", msg, info->message,
               waffle_error_to_string(info->code));
}

bool
GLStateWaffle::valid()
{
    if (!gotValidDisplay())
        return false;

    if (!gotValidConfig())
        return false;

    if (!gotValidSurface())
        return false;

    if (!gotValidContext())
        return false;

    if (!waffle_make_current(waffle_display_, waffle_surface_, waffle_context_)) {
        LogWaffleError("waffle_make_current failed");
        return false;
    }

    init_gl_extensions();

    return true;
}

bool
GLStateWaffle::reset()
{
    if (!gotValidDisplay()) {
        return false;
    }

    if (!waffle_context_) {
        return true;
    }

    if (!waffle_context_destroy(waffle_context_)) {
        LogWaffleError("waffle_context_destroy failed");
    }

    waffle_context_ = 0;

    return true;
}

void
GLStateWaffle::swap()
{
    waffle_window_swap_buffers(waffle_surface_);
}

bool
GLStateWaffle::gotNativeConfig(intptr_t& vid)
{
    if (!gotValidConfig())
        return false;

    vid = (intptr_t) waffle_config_;
    return true;
}

void
GLStateWaffle::getVisualConfig(GLVisualConfig& vc)
{
    if (!gotValidConfig())
        return;

    get_glvisualconfig(waffle_config_, vc);
}

/******************************
 * GLStateWaffle private methods *
 *****************************/

bool
GLStateWaffle::gotValidDisplay()
{
    if (waffle_display_)
        return true;

    waffle_display_ = (waffle_display*)native_display_;
    if (!waffle_display_) {
        Log::error("no native display - this shouldn't happen");
        return false;
    }

    return true;
}

void
GLStateWaffle::get_glvisualconfig(waffle_config* waffle_config, GLVisualConfig& visual_config)
{
    waffle_native_config *n = waffle_config_get_native(waffle_config);
    /*
     * NOTE: This works for WAFFLE_PLATFORM_NULL only.
     *       Other platforms will need something different.
     */
    EGLDisplay dpy = n->null->display.egl_display;
    EGLConfig config = n->null->egl_config;

    free(n);
    eglGetConfigAttrib(dpy, config, EGL_BUFFER_SIZE, &visual_config.buffer);
    eglGetConfigAttrib(dpy, config, EGL_RED_SIZE, &visual_config.red);
    eglGetConfigAttrib(dpy, config, EGL_GREEN_SIZE, &visual_config.green);
    eglGetConfigAttrib(dpy, config, EGL_BLUE_SIZE, &visual_config.blue);
    eglGetConfigAttrib(dpy, config, EGL_ALPHA_SIZE, &visual_config.alpha);
    eglGetConfigAttrib(dpy, config, EGL_DEPTH_SIZE, &visual_config.depth);
    eglGetConfigAttrib(dpy, config, EGL_STENCIL_SIZE, &visual_config.stencil);
}

bool
GLStateWaffle::gotValidConfig()
{
    if (waffle_config_)
        return true;

    if (!gotValidDisplay())
        return false;

    const int32_t config_attribs[] = {
        WAFFLE_RED_SIZE, requested_visual_config_.red,
        WAFFLE_GREEN_SIZE, requested_visual_config_.green,
        WAFFLE_BLUE_SIZE, requested_visual_config_.blue,
        WAFFLE_ALPHA_SIZE, requested_visual_config_.alpha,
        WAFFLE_DEPTH_SIZE, requested_visual_config_.depth,
        WAFFLE_STENCIL_SIZE, requested_visual_config_.stencil,
#if GLMARK2_USE_GLESv2
        WAFFLE_CONTEXT_API, WAFFLE_CONTEXT_OPENGL_ES2,
#elif GLMARK2_USE_GL
        WAFFLE_CONTEXT_API, WAFFLE_CONTEXT_OPENGL,
#endif
        WAFFLE_NONE
    };

    waffle_config_ = waffle_config_choose(waffle_display_, config_attribs);
    if (!waffle_config_) {
        LogWaffleError("waffle_config_choose failed");
        return false;
    }

    return true;
}

bool
GLStateWaffle::gotValidSurface()
{
    if (waffle_surface_)
        return true;

    if (!gotValidDisplay())
        return false;

    if (!gotValidConfig())
        return false;

    waffle_surface_ = (waffle_window*) native_window_;
    if (!waffle_surface_) {
        Log::error("no native window - this shouldn't happen");
        return false;
    }

    return true;
}

bool
GLStateWaffle::gotValidContext()
{
    if (waffle_context_)
        return true;

    if (!gotValidDisplay())
        return false;

    if (!gotValidConfig())
        return false;

    waffle_context_ = waffle_context_create(waffle_config_, NULL);
    if (!waffle_context_) {
        LogWaffleError("waffle_context_create failed");
        return false;
    }

    return true;
}
