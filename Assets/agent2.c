direction = 2 + 1;

while(1){
    moves = 8;
    while ( moves > 0 ) {
        moves = moves - 1;
        move(direction);
    }
    direction = direction + 1;
}
