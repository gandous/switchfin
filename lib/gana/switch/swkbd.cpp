
#if SWITCH

#include <string>
#include <cstring>
#include <switch.h>

static const int BUFFER_SIZE = 128;

std::string get_text(const std::string &initial = "")
{
    char buffer[BUFFER_SIZE];
	SwkbdConfig kbd;

	std::memset(buffer, 0, BUFFER_SIZE);
	Result rc = swkbdCreate(&kbd, 0);
	if (R_FAILED(rc))
		return ("");
	swkbdConfigMakePresetDefault(&kbd);
	swkbdConfigSetTextDrawType(&kbd, SwkbdTextDrawType_Line);
	if (initial != "")
		swkbdConfigSetInitialText(&kbd, initial.c_str());
	swkbdConfigSetStringLenMax(&kbd, BUFFER_SIZE);
	if (R_FAILED(swkbdShow(&kbd, buffer, BUFFER_SIZE))) {
        return ("");
	}
	swkbdClose(&kbd);
	return (std::string(buffer));
}

#endif
