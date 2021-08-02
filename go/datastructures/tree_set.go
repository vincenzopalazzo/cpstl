/**
 * TreeSet data structure implementation in Go language
 * Copyright (C) 2020-2021  Vincenzo Palazzo vincenzopalazzodev@gmail.com
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
package datastructures

type ElemToHash interface {
	Hash() int64
}

type Set interface {
	Put(element *ElemToHash)
	Has(element *ElemToHash) bool
	Size() uint64
	Next() (ElemToHash, bool)
}

type TreeSet struct {
	size uint64
}

func NewTreeSet() Set {
	return &TreeSet {size: uint64(0)}
}

func (instance *TreeSet) Put(element *ElemToHash) {}

func (instance *TreeSet) Has(element *ElemToHash) bool {
	return true
}

func (instance *TreeSet) Size() uint64 {
	return instance.size
}

func (instance *TreeSet) Next() (ElemToHash, bool) {
	return nil, false
}
