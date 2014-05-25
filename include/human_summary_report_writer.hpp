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

#ifndef GUARD_human_summary_report_writer_hpp_5853136519833065
#define GUARD_human_summary_report_writer_hpp_5853136519833065

#include "summary_report_writer.hpp"
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace swx
{

// begin forward declarations

class Stint;

// end forward declarations

class HumanSummaryReportWriter: public SummaryReportWriter
{
// special member functions
public:
	explicit HumanSummaryReportWriter(std::vector<Stint> const& p_stints);
	HumanSummaryReportWriter(HumanSummaryReportWriter const& rhs) = delete;
	HumanSummaryReportWriter(HumanSummaryReportWriter&& rhs) = delete;
	HumanSummaryReportWriter& operator=(HumanSummaryReportWriter const& rhs) = delete;
	HumanSummaryReportWriter& operator=(HumanSummaryReportWriter&& rhs) = delete;
	virtual ~HumanSummaryReportWriter();

// inherited virtual functions
private:
	virtual void do_write_summary
	(	std::ostream& p_os,
		std::map<std::string, unsigned long long> const& p_activity_seconds_map
	) override;

// ordinary member functions
private:
	void print_label_and_rounded_hours
	(	std::ostream& p_os,
		std::string const& p_label,
		unsigned long long p_seconds,
		unsigned int p_left_col_width
	) const;

};  // class HumanSummaryReportWriter

}  // namespace swx

#endif  // GUARD_human_summary_report_writer_hpp_5853136519833065
