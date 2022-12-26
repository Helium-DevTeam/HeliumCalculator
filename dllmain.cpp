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
#include <format>

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
vector<string> hcalc_error_strs;

HeliumExtensionLogger logger("Helium", "Calculator");

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

int hcalc(helium_command_context& ctx)
{
	hcalc_expression_string = ctx.GetArgument<GreedyString>("<expression>");
	const bool is_from_console = ctx.GetSource().get_source() == command_source_e::CONSOLE;
	if (hcalc_expression_string.empty())
	{
		return 0;
	}
	if (!hcalc_expression_parser.compile(hcalc_expression_string, hcalc_expression))
	{
		hcalc_error_strs.clear();
		hcalc_error_strs.push_back(format("Error: {} Expression: {}",
			hcalc_expression_parser.error(),
			hcalc_expression_string));

		for (std::size_t i = 0; i < hcalc_expression_parser.error_count(); ++i)
		{
			error_t error = hcalc_expression_parser.get_error(i);
			hcalc_error_strs.push_back(format("Err: {} Pos: {} Type: [{}] Msg: {} Expression: {}",
				static_cast<unsigned int>(i),
				static_cast<unsigned int>(error.token.position),
				exprtk::parser_error::to_str(error.mode),
				error.diagnostic,
				hcalc_expression_string));
		}

		if (is_from_console) {
			for (auto& error_str : hcalc_error_strs)
			{
				logger.error(error_str);
			}
		}
		return 0;
	}

	const mpfr::mpreal result = hcalc_expression.value();
	const string result_str = result.toString();
	if (is_from_console) {
		logger.info(result_str);
	}
	return 0;
}

HELIUM_EXTENSION_EXPORT int on_self_load()
{
	hcalc_symbol_table.add_constants();
	hcalc_expression.register_symbol_table(hcalc_symbol_table);
	command_dispatcher.Register("#hcalc").Then<Argument, GreedyString>("<expression>").Executes(hcalc);
	return 0;
}

HELIUM_EXTENSION_EXPORT int on_self_unload()
{
	return 0;
}