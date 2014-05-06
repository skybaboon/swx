/*
 * Copyright 2014 Matthew Harvey
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "command.hpp"
#include "help_line.hpp"
#include "info.hpp"
#include "parsed_arguments.hpp"
#include "stream_flag_guard.hpp"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::endl;
using std::left;
using std::ostream;
using std::ostringstream;
using std::runtime_error;
using std::setw;
using std::string;
using std::vector;

namespace swx
{

Command::Command
(	string const& p_command_word,
	vector<string> const& p_aliases,
	string const& p_usage_summary,
	vector<HelpLine> const& p_help_lines
):
	m_command_word(p_command_word),
	m_usage_summary(p_usage_summary),
	m_aliases(p_aliases),
	m_help_lines(p_help_lines)
{
	add_boolean_option
	(	'-',
		"Treat any dash-prefixed arguments after this flag as "
			"ordinary arguments"
	);
}

Command::~Command()
{
}

void
Command::add_boolean_option(char p_flag, string const& p_description)
{
	if (has_boolean_option(p_flag))
	{
		ostringstream oss;
		oss << "Flag already enabled for this Command: " << p_flag;
		throw runtime_error(oss.str());
	}
	m_boolean_options[p_flag] = p_description;
	return;
}

bool
Command::has_boolean_option(char p_flag) const
{
	return m_boolean_options.find(p_flag) != m_boolean_options.end();
}

int
Command::process
(	ParsedArguments const& p_args,
	ostream& p_ordinary_ostream,
	ostream& p_error_ostream
)
{
	auto const flags = p_args.single_character_flags();
	bool has_unrecognized_option = false;
	for (auto c: flags)
	{
		if (!has_boolean_option(c))
		{
			p_error_ostream << "Unrecognized option: " << c << endl;
			has_unrecognized_option = true;
		}
	}
	if (has_unrecognized_option)
	{
		p_error_ostream << "Aborted" << endl;
		return 1;
	}
	auto const error_messages = do_process(p_args, p_ordinary_ostream);
	for (auto const& message: error_messages)
	{
		p_error_ostream << message << endl;
	}
	if (error_messages.empty())
	{
		assert (!has_unrecognized_option);
		return 0;
	}
	assert (error_messages.size() > 0);
	return 1;
}

string
Command::usage_summary() const
{
	return m_usage_summary;
}

string
Command::usage_descriptor() const
{
	// TODO LOW PRIORITY This should handle wrapping of the right-hand cell
	// to a reasonable width if necessary.
	typedef string::size_type ColWidth;
	ColWidth command_word_length = m_command_word.length();
	ColWidth left_col_width = command_word_length;
	auto const app_name = Info::application_name();
	for (auto const& line: m_help_lines)
	{
		ColWidth const left_cell_width =
			line.args_descriptor().length() + command_word_length;
		if (left_cell_width > left_col_width) left_col_width = left_cell_width;
	}
	left_col_width += app_name.length() + 1 + m_command_word.length() + 2;
	ostringstream oss;
	oss << "Usage:\n\n";
	for (auto const& line: m_help_lines)
	{
		StreamFlagGuard guard(oss);
		oss << setw(left_col_width) << left
		    << (app_name + ' ' + m_command_word + ' ' + line.args_descriptor())
			<< "  ";
		guard.reset();
		oss << line.usage_descriptor() << '\n';
	}
	if (!m_aliases.empty())
	{
		oss << "\nAliased as: ";
		auto it = m_aliases.begin();
		oss << *it;
		for (++it; it != m_aliases.end(); ++it) oss << ", " << *it;
	}
	if (!m_boolean_options.empty())
	{
		oss << "\n\nOptions:\n";
		for (auto const& option: m_boolean_options)
		{
			char const c = option.first;
			string const description = option.second;
			oss << "\n-" << c << "     " << description;
		}
	}
	return oss.str();
}

string const&
Command::command_word() const
{
	return m_command_word;
}

vector<string> const&
Command::aliases() const
{
	return m_aliases;
}

}  // namespace swx
