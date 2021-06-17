//
// Created by vincent on 9/14/20.
//
#include <cstdlib>
#include <fstream>
#include <vector>

#include "../HashMap.hpp"
#include "../Queue.hpp"
#include "../Stack.hpp"
#include "TestTool.h"
#include "Utils.h"

void TEST_CASE_ONE_STACK() {
  cpstl::thread_safe::Stack<int> stack;

  std::vector<std::thread> pool;
  pool.reserve(10);

  const int thread = 10000;

  for (std::size_t i = 0; i < thread; i++) {
    std::thread thread{[&stack, i] { stack.push((int)i); }};
    pool.push_back(std::move(thread));
  }

  for (auto &thread : pool) thread.join();

  std::vector<int> result;
  std::vector<int> exp;
  int count = 0;
  while (!stack.is_empty()) {
    auto value = stack.pop();
    result.push_back(*value.get());
    exp.push_back(count);
    count++;
  }

  std::sort(result.begin(), result.end());
  cpstl::assert_equal("TEST_CASE_ONE_STACK", exp, result);
}

void TEST_CASE_ONE_QUEUE() {
  cpstl::thread_safe::Queue<int> queue;

  std::vector<std::thread> pool;

  const int thread = 10000;

  pool.reserve(thread);

  for (std::size_t i = 0; i < thread; i++) {
    std::thread thread{[&queue, i] { queue.push((int)i); }};
    pool.push_back(std::move(thread));
  }

  for (auto &thread : pool) thread.join();

  std::vector<int> result;
  std::vector<int> exp;
  int count = 0;

  while (!queue.is_empty()) {
    auto value = queue.try_pop();
    result.push_back(*value.get());
    exp.push_back(count);
    count++;
  }

  std::sort(result.begin(), result.end());
  cpstl::assert_equal("TEST_CASE_ONE_QUEUE", exp, result);
}

void TEST_CASE_ONE_HASH_MAP() {
  cpstl::thread_safe::HashMap<int, int> map;
  std::vector<std::thread> pool;

  const int thread = 10000;

  pool.reserve(thread);

  for (std::size_t i = 0; i < thread; i++) {
    std::thread thread{[&map, i] { map.add((int)i, (int)i); }};
    pool.push_back(std::move(thread));
  }

  for (auto &thread : pool) thread.join();

  std::vector<int> result;
  std::vector<int> exp;
  for (auto i = 0; i < thread; i++) {
    auto value = map.get_def(i, -1);
    result.push_back(value);
    exp.push_back(i);
  }

  std::sort(result.begin(), result.end());
  cpstl::assert_equal("TEST_CASE_ONE_MAP", exp, result);
}

int main() {
  TEST_CASE_ONE_STACK();
  TEST_CASE_ONE_QUEUE();
  TEST_CASE_ONE_HASH_MAP();
  return EXIT_SUCCESS;
}
