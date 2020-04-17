int main ()
{
    int y;
    int x;

    while( 7 > 3 )
    {
        x = y+1;
        if(x >y)
        {
            y = x;
        }
        else if (x < y)
        {
            x = y;
        }
        else
        {
            x = y;
        }
        
    }

    do
    {
        x = y+1;
        if(x >= y)
        {
            y = x;
        }
        else if (x <= y)
        {
            x = y;
        }
        else if( x == y)
        {
            x = y;
        }
    } while ( x > y);

    
    return 0;
}