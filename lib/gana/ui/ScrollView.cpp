
#include "App.hpp"
#include "ScrollView.hpp"

namespace gana {

ScrollView::ScrollView()
{
    set_draw_propagation(false);
}

ScrollView::~ScrollView()
{}

void ScrollView::draw(NVGcontext *ctx)
{
    nvgScissor(ctx, get_position().x, get_position().y, get_size().x, get_size().y);
    for (auto child: _childs)
        child->propagate_draw(ctx);
    nvgResetScissor(ctx);
}

void ScrollView::enter_tree()
{
    _app->signal_node_focus.connect(*this, &ScrollView::on_node_focus);
}

void ScrollView::on_node_focus(Node *node)
{
    if (has_child(node)) {
        float x = node != nullptr ? node->get_position().x : 0;
        gana::Logger::info("focus %f", x);
        _childs.front()->set_position(Vector2f(-x, _childs.front()->get_position().y));
    }
}

}
