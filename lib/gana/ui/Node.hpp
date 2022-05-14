
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

#define DRAW_DEBUG_RECT nvgBeginPath(ctx);\
    nvgRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y);\
    nvgFillColor(ctx, Color(255, 0, 0, 200).nvg_color());\
    nvgFill(ctx);\

class Node {
    friend class HBoxContainer;
    friend class VBoxContainer;
    friend class RectContainer;
    friend class ScrollView;
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

        virtual void add_child(Node *node);
        virtual void remove_child(Node *node);
        // Return true if the current node has the given node has a child, this call will be call recusively on all child
        // A ScrollContainer will stop the propagation of the function
        virtual bool has_child(const Node *node);
        virtual void draw(NVGcontext *ctx);
        virtual void process_event(Event &evt);
        virtual void update_layout(const Vector2f &size);
        virtual const Vector2f &get_position() const;
        virtual void set_position(const Vector2f &pos);
        virtual const Vector2f &get_gposition() const;
        virtual void set_gposition(const Vector2f &pos);
        virtual const Vector2f &get_size() const;
        // Set the size of the node including margin
        virtual void set_size(const Vector2f &size);
        // Return the min size of the node including margin
        virtual Vector2f get_min_size();
        // Set the min size of the node excluding margin (margin will be added)
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
        virtual bool is_focusable() const;
        // If you want the left/top/right/bottom node to be set automaticaly you need to set
        // focusable to true before adding the node to his parent
        void set_focusable(bool focus);
        virtual void set_left_node(Node *node);
        virtual void set_top_node(Node *node);
        virtual void set_right_node(Node *node);
        virtual void set_bottom_node(Node *node);
        Node *get_left_node();
        Node *get_top_node();
        Node *get_right_node();
        Node *get_bottom_node();
        void set_process(bool process = true);
        void show();
        void hide();
        void set_visible(bool visibility);
        bool is_visible();
        void set_margin(float left, float top, float right, float bottom);
        void set_margin(float margin);
        void set_margin(const Rectf &margin);
        const Rectf &get_margin();
        virtual int get_outline_corner_radius() const;
        template<typename T, typename ...ARGS>
        T *make_managed(ARGS&& ...args);
    protected:
        std::vector<Node*> _childs;
        Rectf _margin;
        App *_app;
        virtual void draw_outline(NVGcontext *ctx);
        virtual void enter_tree();
        virtual void exit_tree();
        virtual void process();
        virtual void on_focus();
        void set_draw_propagation(bool prop);
        void update_min_size();

        // Give the position offset by left and top margin (ready for drawing)
        const Vector2f &get_draw_positon() const;
        // Give the size minus the margin
        const Vector2f &get_draw_size() const;
    private:
        void propagate_enter_tree(App *app);
        void propagate_exit_tree();
        void apply_anchor(const Vector2f &size);
        void propagate_event(Event &evt);
        void propagate_draw(NVGcontext *ctx);
        void check_move_focus_event(Event &evt);
        void update_draw_positon();
        Node *_parent;
        Vector2f _position;
        Vector2f _global_position;
        Vector2f _size;
        Vector2f _min_size;
        Vector2f _real_min_size; // Min size with the node margin added to it
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
        bool _draw_propagation;
        bool _process;
        Vector2f _draw_position;
        Vector2f _draw_size;
        bool _focusable;
};

#include "Node.inl"

}

#endif /* NODE_HPP_ */