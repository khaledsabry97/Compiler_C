int multiply(int n1,int n2)
{
    int multiply;
    multiply = n1 * n2;
    return multiply;
}
int main ()
{
    int n1;
    float n2;
    int n3;
    int n4;
    n1 = 10;
    n2 = 20.5;
    n2 = n1 + n2;
    n2 = n1 - n2;
    n2 = n1 * n2;
    n2 = n1 / n2;
    if(n1 > n2)
    {
        n3 = n1;
    }
    else if( n1 >= n2)
    {
        n3 = n1;
    }
    else if( n1 == n2 )
    {
        n3 = n1;
    }
    else if( n1 != n2)
    {
        n3 = n1;
    }
    else if( n1 < n2)
    {
        n3 = n1;
    }
    else if(n1 <= n2)
    {
        n3 = n1;
    }
    else
    {
         n3 = n1;       
    }

    do
    {

    } while (n1 > n2);
    
    n4 = multiply(n1,n3);
    return 0;
}
