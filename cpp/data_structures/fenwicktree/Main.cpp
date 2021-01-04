/**
 * Binary index tree data structure implementation
 * Copyright (C) 2020  Vincenzo Palazzo vincenzopalazzodev@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include "FenwickTree.hpp"

using namespace cpstl;

int main()
{
    auto tree = BTreeIndex<int>(5);
    tree.update(1, 1);
    tree.update(2, 2);
    tree.update(3, 3);
    tree.update(4, 4);
    tree.update(5, 5);
    std::cout << "------------- insert finisced -----------\n";
    assert(tree.sum(1) == 1);
    assert(tree.sum(2) == 3);
    assert(tree.sum(3) == 6);

    std::cout << "TEST SUITE PASSED\n";
    return EXIT_SUCCESS;
}