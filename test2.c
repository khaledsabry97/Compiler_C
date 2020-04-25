int global_variable;

int multiply(int n1,int n2)
{
    int multiply;
    multiply = n1 * n2;
    return multiply;
}

float multiply(float n1,int n2)
{
    float multiply;
    multiply = n1 * n2;
    return multiply;
}

float multiply(float n1,int n2,int n3)
{
    float multiply;
    multiply = n1 * n2 * n3;
    return multiply;
}
int main ()
{
    int n1;
    float n2;
    int n3;
    int n4;
    const int n5;
    const float n6;
    n5 = 10;
    n6 = 11.5;
    n1 = 10;
    n2 = 20.5;
    n2 = n1 + n2;
    n2 = n1 - n2;
    n2 = n1 * n2;
    n2 = n1 / n2;
    n1 ++;
    n1 --;
    n2 = -n2;

    if(n1 > n2)
    {
        int n8;
        n8 = 10;
        n3 = n1;
    }
    else if( n1 >= n2)
    {
        int n8;
        n8 = 11;
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

    while (n2 > n1)
    {
        int n8;
        n8 = 12;
         n3 = n1;       
         for (n1 =0 ; n1 < 10; n1 = n1 + 1 )
        {
            int n8;
            n8 = 20;
         n3 = n1;       
        }
    }
    
    do
    {
        int n8;
        n8 = 123;
         n3 = n1;       
    } while (n1 > n2);
    
    for (n1 =0 ; n1 < 10; n1 = n1 + 1 )
        {
            int n8;
            n8 = 20;
         n3 = n1;       
        }
    global_variable = 10;

    n4 = multiply(n1,n3);
    n2 = multiply(n2,n3);
    n2 = multiply(n2,n1,n3);

    
    return 0;
}
