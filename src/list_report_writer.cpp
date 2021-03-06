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

#include "list_report_writer.hpp"
#include "report_writer.hpp"
#include "stint.hpp"
#include <vector>

using std::vector;

namespace swx
{

ListReportWriter::ListReportWriter
(   vector<Stint> const& p_stints,
    Options const& p_options
):
    ReportWriter(p_stints, p_options)
{
}

ListReportWriter::~ListReportWriter() = default;

}  // namespace swx
