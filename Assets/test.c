
max_moves = 4;
spin = 3;
direction = 2;

while(1) {

    moves = max_moves;
    while ( moves > 0 ) {
        moves = moves - 1;
        move(direction);
    }
    direction = direction + spin;
}
