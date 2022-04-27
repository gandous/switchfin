
#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <memory>
#include "nanovg/src/nanovg.h"
#include "type/Vector2.hpp"
#include "type/Rect.hpp"
#include "type/Event.hpp"

namespace gana {

class App;

class Node {
    friend class HBoxContainer;
    friend class VBoxContainer;
    friend class RectContainer;
    friend class App;
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

        void add_child(Node *node);
        void remove_child(Node *node);
        virtual void draw(NVGcontext *ctx);
        virtual void process_event(Event &evt);
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
        bool inside_node(const Vector2f &pos) const;
        bool has_focus() const;
        void set_focus(bool focus = true);
        void set_left_node(Node *node);
        void set_up_node(Node *node);
        void set_right_node(Node *node);
        void set_bottom_node(Node *node);
        void set_process(bool process = true);
        void show();
        void hide();
        void set_visible(bool visibility);
        template<typename T>
        T *make_managed();
    protected:
        std::vector<Node*> _childs;
        App *_app;
        virtual void draw_outline(NVGcontext *ctx);
        virtual void enter_tree();
        virtual void exit_tree();
        virtual void process();
    private:
        void propagate_enter_tree(App *app);
        void propagate_exit_tree();
        void apply_anchor(const Vector2f &size);
        void propagate_event(Event &evt);
        void propagate_draw(NVGcontext *ctx);
        void check_move_focus_event(Event &evt);
        Node *_parent;
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
        bool _has_focus;
        Node *_left_node;
        Node *_top_node;
        Node *_right_node;
        Node *_bottom_node;
        std::vector<std::shared_ptr<Node>> _managed_childs;
        bool _visibility;
};

#include "Node.inl"

}

#endif /* NODE_HPP_ */