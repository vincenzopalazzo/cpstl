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
#include <iostream>
#include <cassert>
#include "SegmentTree.h"

using namespace std;
using namespace cpst;

int main()
{
    std::cout << "============== TEST CASE 1 ==============" << "\n";
    vector<int> inputs = {18, 17, 13, 19, 15, 11, 20};
    cout << "Inputs: [";
    for (int i = 0; i < inputs.size(); i++) {
        if (i == inputs.size() - 1) {
            cout << "(" << i + 1 << ", " << inputs[i] << ")" << "]";
            continue;
        }
        cout << "(" << i + 1 << ", " << inputs[i] << "), ";
    }
    cout << "\n";
    auto segment_tree = SegmentTree<int>(inputs);
    int index = segment_tree.range_query(4, 6);
    cout << "Range (4, 6) -> (" << index + 1 << ", " << inputs[index] << ")"  << "\n";
    assert(inputs[index] == 11);

    index = segment_tree.range_query(1, 3);
    cout << "Range (1, 3) -> (" << index + 1 << ", " << inputs[index] << ")"  << "\n";
    assert(inputs[index] == 13);

    segment_tree.update(5, 12);
    cout << "Update element at index 5\n";
    index = segment_tree.range_query(4, 6);
    cout << "Range (4, 6) -> (" << index + 1 << ", " << inputs[index] << ")"  << "\n";
    assert(inputs[index] == 12);


    std::cout << "=========== TEST CASES PASSED ==========" << "\n";
    return EXIT_SUCCESS;
}