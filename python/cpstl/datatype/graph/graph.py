"""
Graph data structure implementation with adjacency list in Python 3
Copyright (C) 2021-2022 Vincenzo Palazzo vincenzopalazzodev@gmail.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
USA.
"""
from abc import ABC, abstractmethod
from typing import Any


class Node:
    """
    Node implementation that contains the value of the element.
    This class contains a list of children and the value of the node.
    """

    def __init__(self, value, opts: dict = None) -> None:
        self.value = value
        self.children = []
        if opts is None:
            self.opts = opts

    def add_node(self, value) -> None:
        node = Node(value)
        self.children.append(node)

    def add_opt(self, key: str, value: Any) -> None:
        """Add the option with the key to the node.

        :param key: Key of the value
        :param value: the value that the user wants to assign
        """
        self.opts[key] = value

    def get_opt(self, key: str) -> Any:
        """Check if the node contains the option

        :param key: the key of the option.
        :return the option is exist None otherwise.
        """
        if key in self.opts:
            return self.opts[key]
        return None

    def get_option_or_def(self, key: str, def_val: Any = None):
        """Get an option wit key if existed, otherwise return the default value.

        :param key: The key of the option
        :param def_val: The default value if not exist, None otherwise
        """
        value = self.get_opt(key)
        if value is None:
            self.add_opt(key, def_val)
        return def_val

    def __hash__(self) -> int:
        return hash(self.value)


class Graph(ABC):
    """Graph interface.

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo
    """

    @abstractmethod
    def add_edge(self, u, v, opts: dict = None):
        """Add the edge from A to b"""
        pass

    @abstractmethod
    def dfs(self) -> None:
        pass

    @abstractmethod
    def bfs(self) -> None:
        pass
