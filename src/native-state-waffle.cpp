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
#include "gl-headers-waffle.h"
#include "native-state-waffle.h"
#include "log.h"

#include <waffle_null.h>

#define DEFINE(type, func, args) type (*func) args;
GLES2_FUNCTION_LIST(DEFINE)
#undef DEFINE

/******************
 * Public methods *
 ******************/

NativeStateWaffle::~NativeStateWaffle()
{
    if (wdpy_)
    {
        if (wwin_)
            waffle_window_destroy(wwin_);

        waffle_display_disconnect(wdpy_);
        waffle_teardown();
    }
}

bool
NativeStateWaffle::init_display()
{
    if (!wdpy_) {
        const int32_t attrib[] = {
            WAFFLE_PLATFORM, WAFFLE_PLATFORM_NULL,
            0
        };
        if (!waffle_init(attrib))
            return false;
        wdpy_ = waffle_display_connect(NULL);
    }

#define LOOKUP(type, func, args)                                       \
    func = (type (*) args) waffle_dl_sym(WAFFLE_DL_OPENGL_ES2, #func); \
    if (!func)                                                         \
        return false;
GLES2_FUNCTION_LIST(LOOKUP)
#undef LOOKUP

    return (wdpy_ != 0);
}

void*
NativeStateWaffle::display()
{
    return (void*)wdpy_;
}

bool
NativeStateWaffle::create_window(WindowProperties const& properties)
{
    if (!wdpy_) {
        Log::error("Error: waffle display has not been initialized!\n");
        return false;
    }

    /* Recreate an existing window only if it has actually been resized */
    if (wwin_) {
        if (properties_.fullscreen != properties.fullscreen ||
            (properties.fullscreen == false &&
             (properties_.width != properties.width ||
              properties_.height != properties.height)))
        {
            waffle_window_destroy(wwin_);
            wwin_ = 0;
        }
        else
        {
            return true;
        }
    }

    /* Set desired attributes */
    properties_.fullscreen = properties.fullscreen;
    properties_.visual_id = properties.visual_id;

    intptr_t attrib[] = {
        /*
         * NOTE: This works for WAFFLE_PLATFORM_NULL only.
         *       Other platforms could call egl/glx-SwapInterval.
         */
        WAFFLE_WINDOW_NULL_VSYNC_WAIT, false,

        WAFFLE_WINDOW_WIDTH, properties.width,
        WAFFLE_WINDOW_HEIGHT, properties.height,
        0
    };
    if (properties_.fullscreen) {
        attrib[2] = WAFFLE_WINDOW_FULLSCREEN;
        attrib[3] = true;
        attrib[4] = 0;
    }

    wwin_ = waffle_window_create2((waffle_config*) properties_.visual_id,
                                  attrib);

    if (!wwin_) {
        Log::error("Error: waffle_window_create() failed!\n");
        return false;
    }

    union waffle_native_window *nw = waffle_window_get_native(wwin_);
    /*
     * NOTE: This works for WAFFLE_PLATFORM_NULL only.
     *       Other platforms will need something different.
     */
    properties_.width = nw->null->width;
    properties_.height = nw->null->height;

    return true;
}

void*
NativeStateWaffle::window(WindowProperties& properties)
{
    properties = properties_;
    return (void*)wwin_;
}

void
NativeStateWaffle::visible(bool visible)
{
    if (visible)
        waffle_window_show(wwin_);
}

bool
NativeStateWaffle::should_quit()
{
    return false;
}
