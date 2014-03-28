/*
 * Copyright 2014 Matthew Harvey
 */

#ifndef GUARD_print_command_processor_23685825347754091
#define GUARD_print_command_processor_23685825347754091

#include "command_processor.hpp"
#include "time_log.hpp"
#include <string>
#include <vector>

namespace swx
{

class PrintCommandProcessor: public CommandProcessor
{
// special member functions
public:
	PrintCommandProcessor
	(	std::string const& p_command_word,
		std::vector<std::string> const& p_aliases,
		TimeLog& p_time_log
	);
	PrintCommandProcessor(PrintCommandProcessor const& rhs) = delete;
	PrintCommandProcessor(PrintCommandProcessor&& rhs) = delete;
	PrintCommandProcessor& operator=(PrintCommandProcessor const& rhs) = delete;
	PrintCommandProcessor& operator=(PrintCommandProcessor&& rhs) = delete;
	virtual ~PrintCommandProcessor();

// inherited virtual functions
private:
	virtual ErrorMessages do_process
	(	Arguments const& p_args,
		std::ostream& p_ordinary_ostream
	) override;

	std::vector<HelpLine> do_get_help_lines() const override;

private:
	TimeLog& m_time_log;

};  // class PrintCommandProcessor

}  // namespace swx

#endif  // GUARD_print_command_processor_hpp_23685825347754091
