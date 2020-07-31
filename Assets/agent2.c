direction = 3;

while(1){
    moves = 4;
    while ( moves > 0 ) {
        moves = moves - 1;
        move(direction);
    }
    direction = direction + 1;
}
