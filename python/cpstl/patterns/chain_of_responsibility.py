"""
Chain of Responsibility Pattern implementation in Python 3
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
from typing import Any, Optional


class IHandler(ABC):
    """Generic interface of a Handler for the chain of responsibility.

    author: https://github.com/vincenzopalazzo
    """

    def on_complete(self, callback_on_complete=None):
        """an optional function that can be called to run.

        :param callback_on_complete: a callback that is called when the handler is returning
        """
        if callback_on_complete is not None:
            callback_on_complete()

    @abstractmethod
    def get_opts(self) -> Optional[Any]:
        """The handler can collect some data, and these data are retrieval with this method.
        If there are any data, a None value is returned."""
        pass

    @abstractmethod
    def handle(self, **kwargs) -> bool:
        """
        handle the logic of the handler, and
        return true to continue in the chain or False otherwise
        :param kwargs: The arguments of the function
        :return True is the chain of responsibility need to continue, False otherwise
        """
        pass


class IChainOfResponsibility(ABC):
    """
    Chain of a responsibility pattern to handler an event throws by the client
    in a sequence of steps.

    author: https://github.com/vincenzopalazzo
    """

    def __init__(self):
        self.handlers = []

    def add_handler(self, handler: IHandler) -> None:
        """Add a handler to the chain of responsibility."""
        self.handlers.append(handler)

    def normal_handle(self, **kwargs) -> Optional[Any]:
        """A pre define function to run the normal chain of
        responsibility."""

        for handler in self.handlers:
            next = handler.handle(**kwargs)
            if not next:
                break
        return None

    @abstractmethod
    def get_opts(self) -> Optional[Any]:
        """The handler can collect some data, and these data are retrieval with this method.
        If there are any data, a None value is returned."""
        pass

    @abstractmethod
    def handle(self, **kwargs) -> Optional[Any]:
        """
        Handle a generic call to a sequence of steps.

        A default implementation of this can be the following one.

        ```python
         def handle(self, **kwargs) -> Optional[Any]:
            return self.normal_handle(kwargs)
        ```

        :param kwargs: the args that the function accepts
        """
        pass
