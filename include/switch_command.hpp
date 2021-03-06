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

#ifndef GUARD_switch_command_hpp_9219790538409627
#define GUARD_switch_command_hpp_9219790538409627

#include "config_fwd.hpp"
#include "recording_command.hpp"
#include "time_log.hpp"
#include <ostream>
#include <string>
#include <vector>

namespace swx
{

class SwitchCommand: public RecordingCommand
{
// special member functions
public:
    SwitchCommand
    (   std::string const& p_command_word,
        std::vector<std::string> const& p_aliases,
        TimeLog& p_time_log
    );
    SwitchCommand(SwitchCommand const& rhs) = delete;
    SwitchCommand(SwitchCommand&& rhs) = delete;
    SwitchCommand& operator=(SwitchCommand const& rhs) = delete;
    SwitchCommand& operator=(SwitchCommand&& rhs) = delete;
    virtual ~SwitchCommand();

// inherited virtual functions
private:
    virtual ErrorMessages do_process
    (   Config const& p_config,
        std::vector<std::string> const& p_ordinary_args,
        std::ostream& p_ordinary_ostream
    ) override;

    virtual bool does_support_placeholders() const override;

// member variables
private:
    bool m_amend = false;
    bool m_create_activity = false;
    bool m_use_regex = false;
    bool m_time_stamp_provided = false;
    std::string m_time_stamp;

};  // class SwitchCommand

}  // namespace swx

#endif  // GUARD_switch_command_hpp_9219790538409627
