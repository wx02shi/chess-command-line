# cs246 Chess Project: Command-line chess game.

## Overview
This project takes advantage of the object-oriented principles taught in CS 246, such as Observer, Strategy, and Visitor design patterns.

This readme provides a general rundown of the project, for our full learnings, open the `demo.pdf`, `design.pdf`, and `uml-final.pdf` to learn more.

Run the program using `./chess`. 

In general, the program was implemented such that pieces aren't aware of their own position. Instead, they all have functions
that return all valid moves given a starting position as input. Hence, the `Board` manages all pieces and (usually) abstracts away positions from other files; 
all attempts to move pieces must be called through the `Board`. (Note that for convenience, the user actually interacts with the `Game` to move pieces)

We refer to a `Piece` p's threatened tiles as tiles which p can move to, or tiles which have teammates that p is protecting.

It should be noted that stalemate is not properly implemented, as such stalemate only occurs when there are no valid moves left
for both players.

## Design
UML Diagram:

### Strategy Design Pattern
This is the most complicated part of the project. The computer class primarily employs this design pattern. 
There are three difficulties. All types of bots have a function called `autoMove`, which takes a `Board` as a parameter.

The Strategy design pattern makes it easy to write the `autoMove` function for many difficulty levels. \
Level 1 computers use the level 1 `Difficulty`, `L1`, to generate a random legal move. It finds all pieces that belong
to the computer player, randomly selects one, generates all of its possible moves, and randomly selects that too. Unbeatable, really.

`L2` computers look for the highest-valued piece the computer player can capture, or if it can engage a check. 

These differing methods have the same basis, requiring to search the entire `Board`, so unifying `L1` and `L2` under the 
`Difficulty` abstract class allows us to call `computerMove` functions without worrying about how they work. All the user
needs to understand is that they're probably playing against harder bots. \
Especially with our basic bots, a high-level player can figure out how to easily beat the bots if they understand their implementation,
which is why it's so important to abstract them away.

Lastly, the strategy design pattern makes it easy to add more difficulties of bots.

### Visitor Design Pattern
The Visitor design pattern is employed to determine the state of the game after each move, primarily to check if there is a check,
or a stalemate. As such, there are two subclasses of `PieceVisitor` called `isStalemateVisitor` and `isCheckVisitor`. 

Both visitors work in similar fashion: upon visiting a `Piece`, they extract all of their valid moves and run some verification logic.
For checks, the `Piece`'s valid moves are checked to see if a King is one a tile to a valid move. For stalemate, it checks if
there are no valid moves to make.

For checkmates, we simply see if there is a check, which King is in check, and if all of that King's valid moves are threatened
by opponent's pieces. This is sufficient logic that is simpler than modifying the traditional Visitor design.

### Observer Design Pattern
The Observer design pattern is used to display the game through various mediums. Currently, there are two observers: 
one prints the board to standard output, and another draws the board in a graphical window. In the future, Observer allows
us to add more robust interaction mediums, perhaps one that isn't running on a sketchy `Xwindow` graphics implementation.

## Pieces
Uppercase is white pieces, lowercase is black (I think)

K: king \
Q: queen \
B: bishop \
N: knight \
R: rook \
P: pawn

## Basic Commands
Run the program using `./chess`. 

The program takes text commands from standard input. \
Using bash, you can redirect file contents into standard input in order to run tests.

## Game Commands
`game human human`: creates a new game to play for two humans. \
`game human computer[x]`: creates a new game to play for a human against a bot of level [x]. The bot can be levels 1, 2, or 3.\
`game computer[x] computer[x]`: creates a new game between two bots. The bots can be different levels if desired.\
`move e2 e3`: when it is a human's turn, moves a piece on tile E2 to E3, if it is a legal move.\
`move`: when it is a bot's turn, the bot will make a move at its own discretion.\
`resign`: ff
### Setup mode
Before a game starts, the user can setup the board to run certain scenarios.

`setup`: enter setup mode with an empty board. Starts in White player's turn to add pieces. \
`+ K a1`: adds a King piece to tile A1.\
`= black`: switches to Black player's turn to add pieces.\
`done`: exit setup mode.
