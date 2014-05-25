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

#ifndef GUARD_csv_summary_report_writer_hpp_5020698078452003
#define GUARD_csv_summary_report_writer_hpp_5020698078452003

#include "summary_report_writer.hpp"
#include "stint.hpp"
#include <ostream>
#include <vector>

namespace swx
{

class CsvSummaryReportWriter: public SummaryReportWriter
{
// special member functions
public:
	explicit CsvSummaryReportWriter(std::vector<Stint> const& p_stints);
	CsvSummaryReportWriter(CsvSummaryReportWriter const& rhs) = delete;
	CsvSummaryReportWriter(CsvSummaryReportWriter&& rhs) = delete;
	CsvSummaryReportWriter& operator=(CsvSummaryReportWriter const& rhs) = delete;
	CsvSummaryReportWriter& operator=(CsvSummaryReportWriter&& rhs) = delete;
	virtual ~CsvSummaryReportWriter();

// inherited virtual member functions
private:
	virtual void do_write_activity_hours
	(	std::ostream& p_os,
		std::string const& p_activity,
		double p_rounded_hours
	);

};  // class CsvSummaryReportWriter

}  // namespace swx

#endif  // GUARD_csv_summary_report_writer_hpp_5020698078452003