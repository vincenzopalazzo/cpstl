/**
 * CPSTL demo to use the TestTool method to make simple test unit
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */
#include <cstdlib>

#include "../GraphList.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;

void TEST_CASE_TWO_BFS() {
  //      2 -> 3 -> 4
  // 1 ->
  //      5 -> 6 -> 7

  cpstl::GraphList<int> graph(true);
  graph.add_edge(1, 2);
  graph.add_edge(2, 3);
  graph.add_edge(3, 4);
  graph.add_edge(1, 5);
  graph.add_edge(5, 6);
  graph.add_edge(6, 7);

  auto result = graph.bfs();
  cpstl::assert_equal("TEST_CASE_BFS", 1, static_cast<int>(result.size()));
  cpstl::assert_equal("TEST_CASE_BFS", {1, 2, 5, 3, 6, 4, 7}, result[0]);
  cpstl::cp_log(LOG, result[0]);
}

void TEST_CAS_THREE_DFS() {
  //      2 -> 4 -> 5
  // 1 ->
  //      3 -> NULL
  //
  cpstl::GraphList<int> graph(true);
  graph.add_edge(1, 2);
  graph.add_edge(1, 3);
  graph.add_edge(2, 4);
  graph.add_edge(4, 5);

  auto result = graph.dfs();
  cpstl::assert_equal("TEST_CASE_DFS", 1, static_cast<int>(result.size()));
  cpstl::assert_equal("TEST_CASE_DFS", {1, 2, 4, 5, 3}, result[0]);
  cpstl::cp_log(LOG, result[0]);
}

int main() {
  TEST_CASE_TWO_BFS();
  TEST_CAS_THREE_DFS();
  return EXIT_SUCCESS;
}
