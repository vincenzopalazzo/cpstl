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

#include "../InvertedIndex.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

const cpstl::Log LOG(true);

static void TEST_ONE_POSTING_LIST_CREATION() {
  auto invertedIndex = cpstl::InvertedIndex();

  invertedIndex.add_file("res/small.txt");

  std::string elem = invertedIndex.to_string();
  cpstl::cp_log(LOG, "----- SMALL FILE -------");
  cpstl::cp_log(LOG, elem);
}

static void TEST_ONE_POSTING_LIST_CREATION_TWO() {
  auto invertedIndex = cpstl::InvertedIndex();

  invertedIndex.add_file("res/sample3.txt");

  std::string table = invertedIndex.to_string();
  cpstl::cp_log(LOG, "------ BIG FILE --------");
  cpstl::cp_log(LOG, table);
}


int main() {
  TEST_ONE_POSTING_LIST_CREATION();
  TEST_ONE_POSTING_LIST_CREATION_TWO();
  return EXIT_SUCCESS;
}
