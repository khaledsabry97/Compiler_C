int n1;
int func1(int n)
{
    return 1;
}



int func2(int n)
{
    return 0;
}

int func1(int n)
{
    return 1;
}

int func1(int n)
{
    return 1;
}
int func1(int n)
{
    return 1;
}

float func1(int n)
{
    return 1;
}


int main ()
{
    int result;
    result = 5 * 2 + 5 * 3;

    result = (3 + 2) / 4 * 10 + 2 + 100;

    if (result > 0)
    {
        int result;
        func1(result);
    } else {
        func2(result);
    }

    {
        int comp1;
        comp1 = 10;
        {
            int comp2;
            comp2 = 20;
        }
    }

    return 0;
}