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

#include "version_command.hpp"
#include "command.hpp"
#include "help_line.hpp"
#include "info.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using std::endl;
using std::ostream;
using std::string;
using std::vector;

namespace swx
{

VersionCommand::VersionCommand
(	string const& p_command_word,
	vector<string> const& p_aliases
):
	Command
	(	p_command_word,
		p_aliases,
		"Print version information",
		vector<HelpLine>{ HelpLine("Print version information") },
		false
	)
{
}

VersionCommand::~VersionCommand()
{
}

Command::ErrorMessages
VersionCommand::do_process
(	ParsedArguments const& p_args,
	ostream& p_ordinary_ostream
)
{
	ErrorMessages error_messages;
	if (!p_args.ordinary_args().empty())
	{
		error_messages.push_back("Too many arguments passed to this command.");
	}
	else
	{
		p_ordinary_ostream << Info::application_name()
						   << " version "
						   << Info::version()
						   << endl;
	}
	return error_messages;
}

}  // namespace swx
