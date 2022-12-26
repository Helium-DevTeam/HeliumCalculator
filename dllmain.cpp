/*
* Helium Calculator i
* You can get the latest source code and releases of Helium Calculator at :
* https://github.com/Helium-DevTeam/HeliumCalculator
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium
*
* Helium is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

#include "Helium.h"

#include <string>
#include <list>
#include <any>

#include <exprtk_mpfr_adaptor.hpp>
#include <exprtk.hpp>

using namespace helium;
using namespace std;
using namespace exprtk;

using hcalc_float_t = mpfr::mpreal;
using symbol_table_t = symbol_table<hcalc_float_t>;
using expression_t = expression<hcalc_float_t>;
using parser_t = parser<hcalc_float_t>;
using error_t = parser_error::type;

symbol_table_t hcalc_symbol_table;
expression_t hcalc_expression;
string hcalc_expression_string;
parser_t hcalc_expression_parser;

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
	return 0;
}

HELIUM_EXTENSION_EXPORT int on_self_load()
{
	hcalc_symbol_table.add_constants();
	hcalc_expression.register_symbol_table(hcalc_symbol_table);
	return 0;
}

HELIUM_EXTENSION_EXPORT int on_self_unload()
{
	return 0;
}
