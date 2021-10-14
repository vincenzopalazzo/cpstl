/**
 * perfect hash function c++ implementation
 * copyright (c) 2020-2021  vincenzo palazzo vincenzopalazzodev@gmail.com
 *
 * this program is free software; you can redistribute it and/or
 * modify it under the terms of the gnu general public license
 * as published by the free software foundation; either version 2
 * of the license, or (at your option) any later version.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * gnu general public license for more details.
 *
 * you should have received a copy of the gnu general public license
 * along with this program; if not, write to the free software
 * foundation, inc., 51 franklin street, fifth floor, boston, ma  02110-1301,
 * usa.
 */
#ifndef LZ77_H
#define LZ77_H

namespace cpstl {

  template <class T = unsigned char>
  class LZ77Item {
  public:
    // the offset of ??
    std::size_t offset;
    // the lenght of ??
    std::size_t lenght;
    // the next element that it
    // is not in a pattern
    T next_elem;

    LZ77Item(std::size_t offset, std::size_t lenght, T next_elem):
      offset(offset), lenght(lenght), next_elem(next_elem) {}
  }

  class LZ77 {
  public:

    /**
     * This the a function that implement the theoretical explanation of the LZ1 algorithm
     * and return a list of tuple that contains the information to decode it.
     */
    std::vector<LZ77Item> compress(std::vector<unsigned char> const &to_compress) {
      return {}
    }

    /**
     * Document it when it is ready to be implemented.
     */
    std::vector<unsigned char> decompress() {
      {}
    }
  };
};

#endif
