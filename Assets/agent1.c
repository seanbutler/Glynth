
max_moves = 2 + rand(16);
spin = 1;
direction = 1;

while(1) {

    moves = max_moves;
    while ( moves > 0 ) {
        moves = moves - 1;
        move(direction);
    }
    direction = direction + spin;
}
