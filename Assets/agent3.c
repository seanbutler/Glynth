
max_moves = 8;
spin = 2;
direction = 0;

while(1) {

    moves = max_moves;

    while ( moves > 0 ) {
        moves = moves - 1;
        move(direction);
    }

    direction = direction + spin;
}
