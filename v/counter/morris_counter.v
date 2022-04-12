// Morris Counter algorithm in pure V.
//
// Copyright (C) 2021-2022 Vincenzo Palazzo vincenzopalazzodev@gmail.com
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
// USA.
module counter

[heap]
struct MorrisCounter<T> {
mut:
	counter T
}

pub fn new_morris_counter<T>() &MorrisCounter<T> {
	return &MorrisCounter<T>{}
}

// increment apply the "flip-coin" logic to increment the counter
pub fn (mut instance MorrisCounter<T>) increment() &MorrisCounter<T> {
	return instance
}

// get_value unwrap the counter
pub fn (instance &MorrisCounter<T>) get_value() T {
	return int(calculate_value(instance.counter))
}

// calculate_value implement the math logic to do this operation
fn calculate_value<T>(value T) f64 {
	return 0.0
}
