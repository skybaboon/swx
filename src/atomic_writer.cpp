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
#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>

using std::feof;
using std::fopen;
using std::fputs;
using std::fread;
using std::rename;
using std::runtime_error;
using std::size_t;
using std::FILE;
using std::string;
using std::vector;

namespace swx
{

namespace
{
	class FileStreamGuard
	{
	public:
		explicit FileStreamGuard(FILE* p_file_stream):
			m_file_stream(p_file_stream)
		{
		}
		~FileStreamGuard()
		{
			if (m_file_stream)
			{
				// TODO Respond appropriately if not successfully closed.
				fclose(m_file_stream);
			}
		}
	private:
		FILE* m_file_stream;
	};
}

AtomicWriter::AtomicWriter(string const& p_filepath):
	m_tempfile(nullptr),
	m_orig_filepath(p_filepath)
{
	// TODO Need to ensure umask is set appropriately. See docs for
	// mkstemp.

	// On construction, we immediately copy the original file to a newly created
	// temp file.

	// NOTE There's a bunch of non-portable stuff in here. POSIX is assumed.
	// This is done consciously: there is no intention of supporting this
	// application for non-POSIX platforms.
	string const sf_template_str = Info::home_dir() + "/.swx_temp_XXXXXX";
	vector<char> vec(sf_template_str.begin(), sf_template_str.end());
	vec.push_back(0);
	char* const temp_filepath = &vec[0];
	int const tempfile_descriptor = mkstemp(temp_filepath);
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
	if ((access(m_orig_filepath.c_str(), R_OK) == 0) || (errno != ENOENT))
	{
		// then the original file exists, and we copy it to the tempfile
		FILE* const infile = fopen(m_orig_filepath.c_str(), "r");
		if (!infile)
		{
			throw runtime_error("Error opening file to read.");
		}
		FileStreamGuard infile_guard(infile);
		size_t const buf_size = 4096;
		char buf[buf_size];
		while (!feof(infile))
		{
			size_t const sz = fread(buf, 1, buf_size, infile);
			if (ferror(infile))
			{
				throw runtime_error("Error reading from file.");
			}
			assert ((sz == buf_size) || feof(infile));
			fwrite(buf, 1, sz, m_tempfile);
			if (ferror(m_tempfile))
			{
				throw runtime_error("Error writing to file.");
			}
		}
	}
	return;
}

AtomicWriter::~AtomicWriter()
{
	// TODO Somehow respond if there was an error closing and deleting the temp
	// file; but don't throw from destructor.
	if (m_tempfile)
	{
		fclose(m_tempfile);
	}
	
	// Might fail if m_tempfile wasn't created - or for other reasons.
	remove(m_temp_filepath.c_str());
}

void
AtomicWriter::append(string const& p_str)
{
	if (fputs(p_str.c_str(), m_tempfile) < 0)
	{
		throw runtime_error("Error appending to file.");	
	}
	return;
}

void
AtomicWriter::append_line(string const& p_str)
{
	append(p_str);
	append("\n");
	return;
}

void
AtomicWriter::append_line()
{
	append("\n");
	return;
}

void
AtomicWriter::commit()
{
	if (rename(m_temp_filepath.c_str(), m_orig_filepath.c_str()))
	{
		throw runtime_error("Error renaming temp file.");
	}
	return;
}

}  // namespace swx