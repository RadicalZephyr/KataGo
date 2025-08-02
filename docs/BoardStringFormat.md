# Board string format

KataGo often represents board positions in tests and JSON data using a simple
ASCII diagram. The following characters are used:

* `X` - black stone
* `O` - white stone
* `.` - empty point
* `#` - wall cell

Walls behave like off-board locations but can appear inside the board. They are
accepted by `Board::parseBoard` and will be emitted by `Board::toStringSimple`
and JSON serialization routines.

Example:

```
X.O..
..#..
.....
.....
.....
```

