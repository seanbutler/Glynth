direction = 0;

while(1)
{
    moves = 5;
    while ( moves > 0 )
    {
        moves = moves - 1;
        move(direction);
    }
    direction = direction + 1;
}
