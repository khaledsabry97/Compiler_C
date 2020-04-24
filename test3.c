int global_variable;

int multiply(int n1,int n2)
{
    int multiply;
    multiply = n1 * n2;
    return multiply;
}

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



float divide(float n1,int n2)
{
    float divide;
    divide = n1 / n2;
    return divide;
}

float divide(float n1,const float n2)
{
    float divide;
    n2 = 10.5;
    divide = n1 / n2;
    return divide;
}

int main ()
{
    int n1;
    float n2;
    int n3;
    int n4;
    int n5;
    int n5;
    const int n6;
    n1 = 10;
    n2 = 20.5;
    n1 = n2;
    n1 = n3;
    n3 = -n1;

    if(n1 > (n1 == n2))
    {
        n3 = n1;
    }

    n4 = multiply(n1,n2);
    n5 = divide(n2,n1);
    n5 = 10;

    n2 = multiply(n2,n1,n3);

    n2 = n1 + n2;
    n2 = n1 - n2;
    n2 = n1 * n2;
    n2 = n1 / n2;
    n1 ++;
    n1 --;
    n2 = -n2;

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

    while (n2 > n1)
    {
         n3 = n1;       
    }
    
    do
    {
         n3 = n1;       
    } while (n1 > n2);
    
    for (n1 =0 ; n1 < 10; n1 = n1 + 1 )
        {
         n3 = n1;       
        }
    global_variable = 10;

    n4 = multiply(n1,n3);
    n2 = multiply(n2,n3);
    n2 = multiply(n2,n1,n3);

    n6 = 10;
    n6 = n1;
    n2 = divide(n2,n2);

    return 0;
}
