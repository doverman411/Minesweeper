Below is a list of the decisions that I made, and why I made them:
    1. The board had the code for printing tiles.
        - This is because a tile's looks depends on whether the game is over or not (amonst other things).
        - Thus, the tile object cannot determine how it should be displayed because it isn't aware of any board it's on.
    2. tilesAround() returns a vector of pointers of Tiles.
        - This is because vector<T>.push_back() pushes a COPY of the argument, rather than a reference.
        - Thus, if it instead returned a vector of copies of tiles, that would be useless as we need to modify the actual tiles on the board.
