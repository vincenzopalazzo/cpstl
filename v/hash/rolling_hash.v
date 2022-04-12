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

// Rolling Hash algorithm in pure V.
//
// author: https://github.com/vincenzopalazzo
struct RollingHash {
	prime_numer u64
}

pub fn new_rolling_hash() RollingHash {
	// FIXME: autogenerate the prime numbers and remove
	// the array
	prime_numbers := [
		62563,
		62581,
		62591,
		62597,
		62603,
		62617,
		62627,
		62633,
		62639,
		62653,
	]
	// FIXME: take this index randomly
	return RollingHash{
		prime_numer: u64(prime_numbers[2])
	}
}

// hash use the Karp Rabin fingerprint to calculate the hash of the string
pub fn (instance &RollingHash) hash(source string) u64 {
	return instance.hash_from_bin(source.bytes())
}

// hash_from_bin use the Karp Rabin fingerprint to calculate the hash of the binary array
pub fn (instance &RollingHash) hash_from_bin(source []byte) u64 {
	mut fingerprint := u64(0)
	for bit in source {
		fingerprint = ((fingerprint * 2) + bit) % instance.prime_numer
	}
	return fingerprint
}
