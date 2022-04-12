
#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <memory>
#include "nanovg/src/nanovg.h"
#include "type/Vector2.hpp"
#include "type/Rect.hpp"

namespace gana {

class App;

class Node {
    friend class HBoxContainer;
    friend class VBoxContainer;
    public:
        Node();
        ~Node();

        enum Layout {
            POSITION,
            ANCHOR,
        };

        enum Sizing {
            FILL,
            SHRINK_BEGIN,
            SHRINK_CENTER,
            SHRINK_END,
        };

        enum Anchor {
            TOP_LEFT = 0,
            TOP_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_RIGHT,

            CENTER_LEFT,
            CENTER_TOP,
            CENTER_RIGHT,
            CENTER_BOTTOM,

            LEFT_WIDE,
            TOP_WIDE,
            RIGHT_WIDE,
            BOTTOM_WIDE,

            CENTER,
            FULL_RECT,
        };

        enum GrowDirection {
            BEGIN,
            END,
            BOTH,
        };

        void add_child(const std::shared_ptr<Node> &node);
        virtual void draw(NVGcontext *ctx);
        virtual void update_layout(const Vector2f &size);
        virtual const Vector2f &get_position() const;
        virtual void set_position(const Vector2f &pos);
        virtual const Vector2f &get_size() const;
        virtual void set_size(const Vector2f &size);
        virtual Vector2f get_min_size();
        virtual void set_min_size(const Vector2f &min_size);
        Sizing get_hsizing() const;
        void set_hsizing(Sizing sizing);
        Sizing get_vsizing() const;
        void set_vsizing(Sizing sizing);
        bool get_expand() const;
        void set_expand(bool expand = true);
        Layout get_layout_mode() const;
        void set_layout_mode(Layout mode);
        const Rectf &get_anchor() const;
        void set_anchor(const Rectf &anchor);
        void set_anchor(Anchor anchor);
        void set_xgrow_direction(GrowDirection direction);
        void set_ygrow_direction(GrowDirection direction);
    protected:
        std::vector<std::shared_ptr<Node>> _childs;
        App *_app;
    private:
        void enter_tree(App *app);
        void apply_anchor(const Vector2f &size);
        Vector2f _position;
        Vector2f _size;
        Vector2f _min_size;
        Layout _layout;
        Sizing _hsizing;
        Sizing _vsizing;
        GrowDirection _hdirection;
        GrowDirection _vdirection;
        bool _expand;
        Rectf _anchor;
};

}

#endif /* NODE_HPP_ */