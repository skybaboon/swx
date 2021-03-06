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

#include "atomic_writer.hpp"
#include "info.hpp"
#include "file_utilities.hpp"
#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using std::cerr;
using std::endl;
using std::fputs;
using std::rename;
using std::runtime_error;
using std::size_t;
using std::FILE;
using std::string;
using std::terminate;
using std::vector;

// NOTE There's a bunch of non-portable stuff in here. POSIX is assumed.

namespace swx
{

AtomicWriter::AtomicWriter(string const& p_filepath):
    m_tempfile(nullptr),
    m_orig_filepath(p_filepath)
{
    // create temp file
    string const sf_template_str = Info::home_dir() + "/.swx_temp_XXXXXX";
    vector<char> vec(sf_template_str.begin(), sf_template_str.end());
    vec.push_back('\0');
    char* const temp_filepath = &vec[0];
    auto const orig_umask = umask(S_IWGRP | S_IWOTH);
    int const tempfile_descriptor = mkstemp(temp_filepath);
    umask(orig_umask);
    if (tempfile_descriptor == -1)
    {
        throw runtime_error("Error opening temp file.");
    }
    m_temp_filepath = temp_filepath;
    m_tempfile = fdopen(tempfile_descriptor, "w+");
    if (!m_tempfile)
    {
        throw runtime_error("Error opening stream to temp file.");
    }
}

AtomicWriter::~AtomicWriter()
{
    if (m_tempfile)
    {
        if (fclose(m_tempfile) != 0)
        {
            cerr << "Error closing temp file. Terminating application." << endl;
            m_tempfile = nullptr;
            terminate();
        }
        m_tempfile = nullptr;
    }
    if (file_exists_at(m_temp_filepath))
    {
        if (remove(m_temp_filepath.c_str()) != 0)
        {
            perror("");
            cerr << "Error removing temp file. Terminating application."
                 << endl;
            terminate();
        }
    }
}

void
AtomicWriter::append(string const& p_str)
{
    if (fputs(p_str.c_str(), m_tempfile) < 0)
    {
        throw runtime_error("Error appending to file.");
    }
}

void
AtomicWriter::append_line(string const& p_str)
{
    append(p_str);
    append("\n");
}

void
AtomicWriter::append_line()
{
    append("\n");
}

void
AtomicWriter::commit()
{
    if (rename(m_temp_filepath.c_str(), m_orig_filepath.c_str()) != 0)
    {
        throw runtime_error("Error renaming temp file.");
    }
}

}  // namespace swx
