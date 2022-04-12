// Rolling Hash algorithm in pure V.
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
module hash

fn test_calculate_hash_multiple_type() {
	hash_fn := new_rolling_hash()
	str := 'the hash of this string need to be equal to each iteration'
	first_hash := hash_fn.hash(str)
	for _ in 0 .. 100 {
		assert hash_fn.hash(str) == first_hash
	}
}
