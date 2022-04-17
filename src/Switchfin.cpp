
#include "Switchfin.hpp"
#include "ui/login/ServerSelect.hpp"

Switchfin::Switchfin(): _app("Switchfin")
{
    std::shared_ptr<ServerSelect> server_select = std::make_shared<ServerSelect>();
    _app.set_root_node(server_select);
}

Switchfin::~Switchfin()
{
}

void Switchfin::run()
{
    _app.run();
}