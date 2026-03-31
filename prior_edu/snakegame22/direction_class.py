"""
Direction utilities used by the Snake game.

This module provides a compact, well-typed `Direction` enum with
helper methods for rotating and converting to movement vectors.
"""
from __future__ import annotations

from enum import IntEnum, unique
from typing import Union
import pygame
from snake_drawing import SNAKE_size

@unique
class Direction(IntEnum):
    """Direction utilities"""
    UP = 0
    RIGHT = 1
    DOWN = 2
    LEFT = 3
    NOWHERE = -1

    def get(val : Union[Direction, str, int], key_map: str = None) -> Direction:
        """Return the direction according to the input vlaue\n
        key_map : 'asdf' or 'arrow'"""
        if type(val) == Direction:
            return val
        if not key_map:
            mapping = {
                "w": Direction(0), ord("w"): Direction(0), pygame.K_UP: Direction(0), 
                "d": Direction(1), ord("d"): Direction(1), pygame.K_RIGHT: Direction(1), 
                "s": Direction(2), ord("s"): Direction(2), pygame.K_DOWN: Direction(2), 
                "a": Direction(3), ord("a"): Direction(3), pygame.K_LEFT: Direction(3), 
            }
        elif key_map == 'asdf':
            mapping = {
                ord("w"): Direction(0), ord("d"): Direction(1),
                ord("s"): Direction(2), ord("a"): Direction(3),
            }
        elif key_map == 'arrow':
            mapping = {
                pygame.K_UP: Direction(0), pygame.K_RIGHT: Direction(1), 
                pygame.K_DOWN: Direction(2), pygame.K_LEFT: Direction(3), 
            }
        if val in mapping.keys():
            return mapping[val]
        return Direction(-1)



    def turn_right(self) -> Direction:
        """Return the direction after a 90-degree clockwise turn."""
        return Direction((int(self) + 1) % 4)

    def turn_left(self) -> Direction:
        """Return the direction after a 90-degree counter-clockwise turn."""
        return Direction((int(self) - 1) % 4)

    def opposite(self) -> Direction:
        """Return the opposite direction (180 degrees)."""
        return Direction((int(self) + 2) % 4)

    def to_vector(self) -> tuple[int, int]:
        """Return the (dx, dy) vector for moving one step in this direction."""
        return {
            Direction.UP: (0, -SNAKE_size),
            Direction.RIGHT: (SNAKE_size, 0),
            Direction.DOWN: (0, SNAKE_size),
            Direction.LEFT: (-SNAKE_size, 0),
        }[self]

    def __str__(self) -> str:  # pragma: no cover - trivial
        return self.name


if __name__ == "__main__":
    # Small demonstration / smoke test when run as a script.
    print(pygame.K_UP, pygame.K_DOWN, pygame.K_RIGHT, pygame.K_LEFT)
    print(Direction.get(pygame.K_DOWN))
    current = Direction.LEFT
    print(current.turn_right())
    print(Direction.UP.turn_left())
    print(Direction.RIGHT.opposite())
    print(Direction.UP.to_vector())