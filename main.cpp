#include <iostream>
#include "justargs.h"

int main( int argc, char * argv[] )
{
    /* variables to be used in ths application */
    bool verbose;
    int age;
    double height;
    std::string name;


    /* Contruct justargs class */
    justargs cmdline( argc, argv );



    /* get parameters from command line into variables */
    if( (cmdline.getparameter( verbose, "-v", "--verbose" )) != 0 )
    {
        std::cerr << "Parameter verbose not present or of wrong type!\n";
        return 1;
    }


    /* get parameter with only shortname */
    if( (cmdline.getparameter( age, "-a", "" )) != 0 )
    {
        std::cerr << "Parameter age not present or of wrong type!\n";
        return 1;
    }


    /* get parameter with only longname */
    if( (cmdline.getparameter( name, "", "--name" )) != 0 )
    {
        std::cerr << "Parameter height not present or of wrong type!\n";
        return 1;
    }


    /* get parameter with both long and short names */
    if( (cmdline.getparameter( height, "-h", "--height" )) != 0 )
    {
        std::cerr << "Parameter height not present or of wrong type!\n";
        return 1;
    }

    
    std::cout << "Information given is:\n";
    std::cout << " Name: " << name << std::endl;
    std::cout << " Age: " << age << std::endl;
    if( verbose )
        std::cout << " Height: " << height << std::endl;


    return 0;
}