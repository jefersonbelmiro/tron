## tron.c

The classic arcade game TRON implemented in C using the ncurses library. 

[![asciicast](https://asciinema.org/a/7qzzspamyqb17efz9ykf58iou.png)](https://asciinema.org/a/7qzzspamyqb17efz9ykf58iou?autoplay=1)

### Features
  - A two player game mode.
   The opponent is played by a bot, which is a very simplistic version of what's described here : http://www.a1k0n.net/2010/03/04/google-ai-postmortem.html
  - An implementation of the Minimax Algorithm, optimized with Alpha-Beta Pruning. 
  - An intelligent heuristic, a few funtions applied onto the game's Voronoi Diagram.
  - An implementation of Dijkstra's Algorithm for square grids.
  - Terminal based UI using Curses.

### Dependencies
  - Ncurses

### install and run

You maybe have to install ncurses library
```sh
sudo apt-get install libncurses5-dev
```

compile
```sh
make
```

run
```sh
bin/game
```

test
```sh
make test
```
