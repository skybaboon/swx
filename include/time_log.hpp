/*
 * Copyright 2014 Matthew Harvey
 */

#ifndef GUARD_time_log_hpp_6591341885082117
#define GUARD_time_log_hpp_6591341885082117

#include "activity.hpp"
#include "activity_id.hpp"
#include "time_point.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace swx
{

class TimeLog
{
// nested types and typedefs
private:

	struct Entry
	{
		ActivityId activity_id;
		TimePoint time_point;
	};

// special member functions
public:
	explicit TimeLog(std::string const& p_filepath);

	TimeLog() = delete;
	TimeLog(TimeLog const& rhs) = delete;
	TimeLog(TimeLog&& rhs) = delete;
	TimeLog& operator=(TimeLog const& rhs) = delete;
	TimeLog& operator=(TimeLog&& rhs) = delete;
	~TimeLog() = default;

/// ordinary member functions
private:
	void load(std::string const& p_filepath);
	ActivityId register_activity(std::string const& p_activity_name);
	void register_entry(std::string const& p_entry_string);

// member variables
private:
	std::vector<Entry> m_entries;
	std::vector<Activity> m_activities;
	std::unordered_map<std::string, ActivityId> m_activity_map;

};  // class TimeLog

}  // namespace swx

#endif  // GUARD_time_log_hpp_6591341885082117
