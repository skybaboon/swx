/*
 * Copyright 2015 Matthew Harvey
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

#include "csv_row.hpp"
#include <iostream>
#include <ostream>
#include <string>

using std::ostream;
using std::endl;
using std::string;

namespace swx
{

CsvRow::CsvRow()
{
    enable_exceptions(m_contents);
}

string
CsvRow::str() const
{
    return m_contents.str();
}

template <>
CsvRow&
CsvRow::operator<<(string const& p_contents)
{
    if (m_started) m_contents << ',';
    if (p_contents.find_first_of(",\"\n\r") == string::npos)
    {
        // no need to quote
        m_contents << p_contents;
    }
    else
    {
        // need to quote and escape
        m_contents << '"';
        for (auto const c: p_contents)
        {
            m_contents << c;
            if (c == '"') m_contents << c;
        }
        m_contents << '"';
    }
    m_started = true;
    return *this;
}

ostream&
operator<<(ostream& p_os, CsvRow const& p_csv_row)
{
    return p_os << p_csv_row.str() << endl;
}

}  // namespace swx
