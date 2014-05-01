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

#include "print_command.hpp"
#include "command.hpp"
#include "help_line.hpp"
#include "reporting_command.hpp"
#include "string_utilities.hpp"
#include "time_log.hpp"
#include <ostream>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

namespace swx
{

PrintCommand::PrintCommand
(	string const& p_command_word,
	vector<string> const& p_aliases,
	TimeLog& p_time_log
):
	ReportingCommand
	(	p_command_word,
		p_aliases,
		vector<HelpLine>
		{	HelpLine("Print summary of time spent on all activities."),
			HelpLine("Print summary of time spent on ACTIVITY", "ACTIVITY")
		},
		p_time_log
	)
{
}

PrintCommand::~PrintCommand()
{
}

Command::ErrorMessages
PrintCommand::do_process
(	Arguments const& p_args,
	ostream& p_ordinary_ostream
)
{
	ErrorMessages ret;
	if (p_args.empty())
	{
		print_report(p_ordinary_ostream);
	}
	else
	{
		string const activity = squish(p_args.begin(), p_args.end());
		print_report(p_ordinary_ostream, &activity);
	}
	return ret;
}

}  // namespace swx
