/**
 * Segment tree data structure implementation
 * Copyright (C) 2020  Vincenzo Palazzo vincenzopalazzodev@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <cstdlib>
#include <vector>
#include "../PersistentSegmentTree.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;

void TEST_CASE_ONE()
{
    vector<int> inputs = {18, 17, 13, 19, 15, 11, 20};
    cpstl::print_vector(inputs);
    auto segment_tree = cpstl::PersistentSegmentTree<int>(inputs);
    int index = segment_tree.range_query(4, 6);
    cpstl::assert_equal("RANGE(4, 6)", 11, index);

    index = segment_tree.range_query(1, 3);
    cpstl::assert_equal("RANGE(1, 3)", 13, index);

    segment_tree.update(5, 16);
    index = segment_tree.range_query(4, 6);
    cpstl::assert_equal("UPDATE RANGE(4, 6)", 15, index);

    index = segment_tree.range_query(5, 6);
    cpstl::assert_equal("RANGE(6, 7)", 16, index);

    index = segment_tree.range_query(6, 6);
    cpstl::assert_equal("RANGE(7, 7)", 20, index);

    index = segment_tree.range_query(1, 3);
    cpstl::assert_equal("RANGE(1, 3)", 13, index);

    index = segment_tree.range_query(0, 1);
    cpstl::assert_equal("RANGE(0, 1)", 17, index);

    segment_tree.update(6, 8);
    index = segment_tree.range_query(5, 6);
    cpstl::assert_equal("UPDATE RANGE(7, 7)", 8, index);
}

int main()
{
    TEST_CASE_ONE();
    return EXIT_SUCCESS;
}