#include "Helium.h"

#include <string>
#include <list>
#include <any>

#include <exprtk.hpp>

using namespace Helium;
using namespace std;
using namespace exprtk;

HELIUM_EXTENSION_EXPORT map<string, string> extension_metadata()
{
	return {
		{"extension_name", "Helium Calculator"},
		{"author", "Helium DevTeam"},
		{"url", "https://github.com/Helium-DevTeam/HeliumCalculator"},
		{"description", "A official calculator extension for Helium."},
		{"helium_version", ">=0.8.45-alpha.0"}
	};
}

int hcalc(string_view event_name, list<any> param)
{
	
}

HELIUM_EXTENSION_EXPORT int on_self_load()
{
	return 0;
}

HELIUM_EXTENSION_EXPORT int on_self_unload()
{
	return 0;
}
