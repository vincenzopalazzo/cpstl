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

// check if the value is around 95% of the real value
fn test_use_morris_counter() {
	mut counter := new_morris_counter<int>()
	for _ in 0..9000 {
		counter.increment()
	}

	value := counter.get_value()
	assert value > 800 && value < 980
}
