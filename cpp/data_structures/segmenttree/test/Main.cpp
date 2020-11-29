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
#include "../SegmentTree.h"
#include "Utils.hpp"
#include "TestTool.hpp"

using namespace std;
using namespace cpstl;

void TEST_CASE_ONE()
{
    vector<int> inputs = {18, 17, 13, 19, 15, 11, 20};
    print_vector(inputs);
    auto segment_tree = SegmentTree<int>(inputs);
    int index = segment_tree.range_query(4, 6);
    cout << segment_tree.get_elem(6);
    assert_equal("RANGE(4, 6)", 11, inputs[index]);

    index = segment_tree.range_query(1, 3);
    assert_equal("RANGE(1, 3)", 13, inputs[index]);

    segment_tree.update(5, 12);
    index = segment_tree.range_query(4, 6);
    assert_equal("RANGE(4, 6)", 12, inputs[index]);

    index = segment_tree.range_query(5, 6);
    assert_equal("RANGE(6, 7)", 12, inputs[index]);

    index = segment_tree.range_query(1, 3);
    assert_equal("RANGE(1, 3)", 13, inputs[index]);

    index = segment_tree.range_query(0, 1);
    assert_equal("RANGE(0, 1)", 17, inputs[index]);
}

int main()
{
    TEST_CASE_ONE();
    return EXIT_SUCCESS;
}