# Chess

https://user-images.githubusercontent.com/56195457/121944122-94a84480-cd52-11eb-8c52-7112ab517e22.mp4

Chess follows all the rules of classic chess game (Castling, En Passant move etc.) AI is implemented with Alpha Beta pruning. Difficulty of the AI sets the depth of MinMax search.

## Run

To run chess run the command `make run`

## Commands

All commands are case sensitive.

- `play [p|c][p|c][1|2|3|4|5]` creates a game of chess, first position is the white player, the second is the black player. `p` represents a real player while `c` is computer. Difficulty of the computer can be set on the scale 1-5 (eg. `play pc4` create a game against computer playing black with difficulty 4)              
- `save [filename]` saves a chess game (`filename`) (filename cannot contain whitespace)
- `load [filnename]` loads a chess game from file (`filename`) (filename cannot contain whitespace)
- `board` shows current chess board
- `move [a|b|c|d|e|f|g|h][1|2|3|4|5|6|7|8][a|b|c|d|e|f|g|h][1|2|3|4|5|6|7|8][q|r|b|n]` moves a chess piece (eg. `move a2b1` moves a chess piece on the position a2 to the position b1), if the moved piece is a pawn and after the move the pawn should promote a chess piece is required for the pawn to promote to (eg. `move a7b8q` promotes a pawn to a queen)
- `restart` restarts the game
- `help` shows help
- `quit` quits the game

White pieces are in capital letters whereas black pieces are in lower letters.

Example of CLI of the game chess:
```
Enter a command, for help enter the command 'help':
$ board
Side to turn: WHITE
    A B C D E F G H
  +-----------------+
8 | r n b q k b n r | 8
7 | p p p p p p p p | 7
6 | . . . . . . . . | 6
5 | . . . . . . . . | 5
4 | . . . . . . . . | 4
3 | . . . . . . . . | 3
2 | P P P P P P P P | 2
1 | R N B Q K B N R | 1
  +-----------------+
    A B C D E F G H
Enter a command, for help enter the command 'help':
```
