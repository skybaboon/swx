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

#include "time_point.hpp"
#include "config.hpp"
#include <chrono>
#include <cstring>
#include <ctime>
#include <memory>
#include <stdexcept>
#include <string>

namespace chrono = std::chrono;

using std::localtime;
using std::memset;
using std::mktime;
using std::runtime_error;
using std::string;
using std::tm;
using std::time_t;
using std::unique_ptr;

namespace swx
{

TimePoint
now()
{
	return chrono::system_clock::now();
}

TimePoint
day_begin(TimePoint const& p_time_point)
{
	tm time_tm = time_point_to_tm(p_time_point);
	time_tm.tm_hour = time_tm.tm_min = time_tm.tm_sec = 0;
	time_tm.tm_isdst = -1;
	return tm_to_time_point(time_tm);
}

TimePoint
day_end(TimePoint const& p_time_point)
{
	tm time_tm = time_point_to_tm(p_time_point);
	time_tm.tm_hour = time_tm.tm_min = time_tm.tm_sec = 0;
	++time_tm.tm_mday;
	return tm_to_time_point(time_tm);
}

std::tm
time_point_to_tm(TimePoint const& p_time_point)
{
	time_t const time_time_t = chrono::system_clock::to_time_t(p_time_point);
	tm* const time_tm_ptr = localtime(&time_time_t);
	return *time_tm_ptr;
}

TimePoint
tm_to_time_point(tm const& p_tm)
{
	tm time_tm = p_tm;
	time_t const time_time_t = mktime(&time_tm);
	return chrono::system_clock::from_time_t(time_time_t);
}

TimePoint
time_stamp_to_point(string const& p_time_stamp)
{
	// don't make this static - caused odd bug with strptime
	string const format_str = Config::format_string();
	char const* format = format_str.c_str();
	tm tm;
	memset(&tm, 0, sizeof(tm));
	tm.tm_isdst = -1;
	bool parse_error = false;
	
	// non-portable
	if (strptime(p_time_stamp.c_str(), format, &tm) == nullptr)
	{
		parse_error = true;
	}

	if (parse_error)
	{
		throw runtime_error("Could not parse timestamp.");
	}
	return chrono::system_clock::from_time_t(mktime(&tm));
}

string
time_point_to_stamp(TimePoint const& p_time_point)
{
	// don't make this static - caused odd bug with strptime
	string const format_str = Config::format_string();
	char const* format = format_str.c_str();
	tm const time_tmp = time_point_to_tm(p_time_point);
	auto const buf_len = Config::formatted_buf_len();
	unique_ptr<char[]> buf(new char[buf_len]);
	if (strftime(buf.get(), buf_len, format, &time_tmp) == 0)
	{
		throw runtime_error("Error formatting TimePoint.");
	}
	string const ret(buf.get());
	return ret;
}

}   // namespace swx
