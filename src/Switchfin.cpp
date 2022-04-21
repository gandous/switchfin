
#include "Switchfin.hpp"

Switchfin::Switchfin(): _app("Switchfin")
{
    _app.set_root_node(&_server_select);
}

Switchfin::~Switchfin()
{}

void Switchfin::run()
{
    _app.run();
}