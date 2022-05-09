
#include "simpleini/SimpleIni.hpp"
#include "config.hpp"
#include "network/JellyfinClient.hpp"
#include "ui/login/ServerSelect.hpp"
#include "ui/home/Home.hpp"
#include "gana/ui/NavigationManager.hpp"
#include "Switchfin.hpp"

Switchfin::Switchfin(): _app("Switchfin")
{
    FILE *f = fopen(SERVER_CONFIG_PATH, "r");

    if (f == nullptr) {
        _current = std::make_shared<ServerSelect>();
    } else {
        CSimpleIni ini;

        ini.LoadFile(f);
        std::shared_ptr<JellyfinClient> client = std::make_shared<JellyfinClient>(ini.GetValue("SERVER", "address", ""));
        client->set_token(ini.GetValue("SERVER", "token"));
        client->set_user_id(ini.GetValue("SERVER", "user_id"));
        std::shared_ptr<gana::NavigationManager> manager = std::make_shared<gana::NavigationManager>();
        manager->navigate_down<Home>(client);
        manager->set_anchor(gana::Node::Anchor::FULL_RECT);
        _current = manager;
        fclose(f);
    }
    _app.set_root_node(_current);
}

Switchfin::~Switchfin()
{}

void Switchfin::run()
{
    _app.run();
}