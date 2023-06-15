/*
 * Copyright (c) 2023, Tim Flynn <trflynn89@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Forward.h>
#include <LibWeb/Painting/PaintableBox.h>
#include <LibWeb/PixelUnits.h>

namespace Web::Painting {

class MediaPaintable : public PaintableBox {
    JS_CELL(MediaPaintable, PaintableBox);

protected:
    explicit MediaPaintable(Layout::ReplacedBox const&);

    static Optional<DevicePixelPoint> mouse_position(PaintContext&, HTML::HTMLMediaElement const&);
    static void fill_triangle(Gfx::Painter& painter, Gfx::IntPoint location, Array<Gfx::IntPoint, 3> coordinates, Color color);

    void paint_media_controls(PaintContext&, HTML::HTMLMediaElement const&, DevicePixelRect media_rect, Optional<DevicePixelPoint> const& mouse_position) const;

private:
    struct Components {
        DevicePixelRect control_box_rect;
        DevicePixelRect playback_button_rect;

        DevicePixelRect timeline_rect;
        DevicePixels timeline_button_size;

        String timestamp;
        RefPtr<Gfx::Font> timestamp_font;
        DevicePixelRect timestamp_rect;
    };

    virtual bool wants_mouse_events() const override { return true; }
    virtual DispatchEventOfSameName handle_mouseup(Badge<EventHandler>, CSSPixelPoint, unsigned button, unsigned modifiers) override;
    virtual DispatchEventOfSameName handle_mousemove(Badge<EventHandler>, CSSPixelPoint, unsigned buttons, unsigned modifiers) override;

    Components compute_control_bar_components(PaintContext&, HTML::HTMLMediaElement const&, DevicePixelRect media_rect) const;
    static void paint_control_bar_playback_button(PaintContext&, HTML::HTMLMediaElement const&, Components const&, Optional<DevicePixelPoint> const& mouse_position);
    static void paint_control_bar_timeline(PaintContext&, HTML::HTMLMediaElement const&, Components const&, Optional<DevicePixelPoint> const& mouse_position);
    static void paint_control_bar_timestamp(PaintContext&, Components const&);
};

}
