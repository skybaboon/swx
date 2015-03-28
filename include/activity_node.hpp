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

#ifndef GUARD_activity_node_hpp_591135825771436
#define GUARD_activity_node_hpp_591135825771436

#include <string>

namespace swx
{

/**
 * Represents an activity in a tree structure. "Level" corresponds to
 * distance from leaf, with leaf nodes having a level of 0.
 */
class ActivityNode
{
// special member functions
// TODO Make sure the copy and assignment operations are exception-safe
public:
	ActivityNode(std::string const& p_activity, unsigned int p_level);
	ActivityNode(ActivityNode const& rhs) = default;
	ActivityNode(ActivityNode&& rhs) = default;
	ActivityNode& operator=(ActivityNode const& rhs) = default;
	ActivityNode& operator=(ActivityNode&& rhs) = default;
	~ActivityNode() = default;

// ordinary member functions
// TODO document these better
public:
	std::string const& activity() const;
	unsigned int level() const;
	unsigned int num_components() const;
	void set_num_components(unsigned int p_num_components);  // can only increase
	ActivityNode parent() const;
	std::string marginal_name() const;

// member variables
private:
	unsigned int const m_level;
	std::string m_activity;

};  // class ActivityNode


// non-member functions

bool operator<(ActivityNode const& lhs, ActivityNode const& rhs);

}  // namespace swx

#endif  // GUARD_activity_node_hpp_591135825771436
