# Chess Game

## Interface
Two player interactive chess mode (Player vs Computer not supported)

Enter your move in the format
```
playerName > MOVE <piece> <destinationsq>
```
OR
```
playerName > CASTLE LEFT/RIGHT
```
After this, it will display the updated board after the move (with capture if apt).

If the move is illegal it will display an error message and expect the player to repeat the move.

It will display a warning whenever there is a check and a message whenever a piece is captured.

It will display the winner if checkmate or tie if stalemate.

Note that there is no allowance for retracing of moves. Once a move is done, it is committed.

The pieces are numbered
```
PWN1 - PWN8 [Left to right]
KNT1 - KNT2 [left to right]
BSP1 - BSP2 [Left to right]
ROK1 - ROK2 [Left to right]
QWN1 - QWN9 [Original 1, 2-9 pawn promotions]
KING
```

The tiles are numbered A1 - H8. Here A - H numbering means left to right and 1 - 8 bottom to top.

As usual, white starts at the bottom (rows 1 and 2) with black at top (rows 7 and 8), both spanning all 8 columns (A - H) with kings at E1 or E8.
