
max_moves = 4;
spin = 1;
direction = 0;

while(1) {

    moves = max_moves;
    while ( moves > 0 ) {
        output = moves;
        output = direction;

        move(direction);
        moves = moves - 1;
    }

    direction = direction + spin;
}
