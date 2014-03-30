/*
 * Copyright 2014 Matthew Harvey
 */

#ifndef GUARD_command_router_hpp_6901861572126794
#define GUARD_command_router_hpp_6901861572126794

#include "command_processor.hpp"
#include "time_log.hpp"
#include <memory>
#include <ostream>
#include <string>
#include <map>
#include <utility>
#include <vector>

namespace swx
{

class CommandRouter
{
// nested types
private:
	typedef
		std::shared_ptr<CommandProcessor>
		CommandProcessorPtr;
	typedef
		std::map<std::string, CommandProcessorPtr>
		CommandProcessorMap;

// special member functions
public:
	explicit CommandRouter(TimeLog& p_time_log);
	CommandRouter(CommandRouter const& rhs) = delete;
	CommandRouter(CommandRouter&& rhs) = delete;
	CommandRouter& operator=(CommandRouter const& rhs) = delete;
	CommandRouter& operator=(CommandRouter&& rhs) = delete;
	~CommandRouter() = default;

// ordinary and static member functions
private:
	void populate_command_processor_map();

public:
	int process_command
	(	std::string const& p_command,
		std::vector<std::string> const& p_args
	) const;


	/**
	 * @throws std::runtime_error if p_command is not a registered
	 * command word.
	 */
	std::string help_information(std::string const& p_command) const;

	/**
	 * In each element \e e of the returned vector, \e e.first is
	 * the main command word, and \e e.second is a vector of aliases
	 * for that command word.
	 */
	std::vector<std::pair<std::string, std::vector<std::string>>>
		available_commands() const;

	static std::string directions_to_get_help();

	static std::string error_message_for_unrecognized_command
	(	std::string const& p_command
	);

private:
	int process_unrecognized_command(std::string const& p_command) const;

public:
	std::ostream& ordinary_ostream() const;
	std::ostream& error_ostream() const;
	void create_command(CommandProcessorPtr const& p_cpp);
	void register_command_word
	(	std::string const& p_word,
		CommandProcessorPtr const& p_cpp
	);

// member variables
private:
	TimeLog& m_time_log;
	CommandProcessorMap m_command_processor_map;

};  // class CommandRouter

}  // namespace swx

#endif  // GUARD_command_router_hpp_6901861572126794
