# GobletGobblers
  Description of the project
    This project is aimed to implement a two players game, close to the Tic-Tac-Toe game. The rules of the games are described below.

    The project is divided into various files. Mostly, the engine of the game, implementing the detailed rules, is provided in the files  board.c and board.h

  Detailed rules of the game.
    The game is played by two players on a three by three squares board, though variants may be played on larger boards. Each player has control of a set of six pieces whose owner is easily identifiable, for example by the shape or the color of the piece. The pieces are of three different sizes (big, medium, small), each player having two of each size.

    During the course of the game, players alternately make a move that consists in either:

    adding a piece from their collection on the board.
    moving one of his visible pieces already on the board to another square.
    A piece can be placed either on an empty square, or on a square containing only smaller pieces, independently of who owns the piece. In that latter case, the piece covers and hide the smaller pieces. When a piece placed over other pieces is moved from a square, the largest piece covered is revealed and can be played in a later turn.

    The game is won by the first player who manages to make a visible line of his pieces across the board (on a line, a column, or a diagonal, like for Tic-Tac-Toe.)

Autor : LEBOCQ Titouan
