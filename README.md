# Battleship
The good-old board/pen and paper strategy guessing game terminalised.:)
I used the logic of the pen/paper version in the development. Overview below is just a summary of the gameplay. For a vivid explanation visit https://en.wikipedia.org/wiki/Battleship_(game).
Or https://www.youtube.com/watch?v=1aAQaGxCpCg for a tutorial

# Overview
Battleship is a multiplayer strategy type guessing game which imitates a seawar between two different captains. Both players have two individual 10x10 grids/boards. One grid shows a player's placed ships and the other serves as a reference to the opponent's ships.
First both players are allowed to place 5 different ships of different sizes on the grids by using RowColumn positioning(E.g. a7) with indication of the direction(that is upwards, downwards, leftwards or rightwards) of the specified ship.
Guesses(again, with RowColumn positioning) are made in turns to hit parts of opponent's ships till they sink. "Misses" and "hits", denoted by 'O' and 'X' respectively, are shown on each player's opponent reference grid to identify next moves.

Main objective of each player is to destroy all the opposing player's fleets. Hence, the game is over when all of a player's ships has been sunk, with the opposing player consequently having the lesser number of sunk ships being the winner.

# New Features
- Single and Multiplayer modes
- Cpu difficulty level

# Updates to be made
- Improve Cpu feature for harder difficulty level
- Add about and how to play sections
- Possible addition of color codes for ships
