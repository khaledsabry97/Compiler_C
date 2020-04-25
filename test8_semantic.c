int count;


int main ()
{
    //second identification for same variable name and type
    int count;
    int no_value;
    count = 10 ;
    
    //add no_value for expression without assign in value to it
    count = count + no_value ;

    // use a variable without identification
    //counts = 10;
    counts = count + no_value ;

    for ( count = 10 ; count < 100 ; count = count + 1 )
    {
        //check it can use outside declaration in other blocks
        no_value = 10;
    }





  
    return 0;
}