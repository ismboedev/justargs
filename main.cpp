#include <iostream>
#include "justargs.h"

int main( int argc, char * argv[] )
{
    /* variables to be used in ths application */
    bool help;
    bool verbose;
    int age;
    double height;
    std::string name;


    /* Contruct justargs class */
    justargs cmdline( argc, argv );


    /* check if help is present, if so print help and exit */
    if(  (cmdline.getparameter( help, "-h", "--help" )) < justargsFAIL )
    {
        std::cout << "This is a not so helpful helpscreen\n";
        return 0;
    }


    /* simples checks */
    /* get parameters from command line into variables */
    if( (cmdline.getparameter( verbose, "-v", "--verbose" )) != justargsOK )
    {
        std::cerr << "Parameter verbose not present or of wrong type!\n";
        return 1;
    }


    /* get parameter with only shortname */
    if( (cmdline.getparameter( age, "-a", "" )) != justargsOK )
    {
        std::cerr << "Parameter age not present or of wrong type!\n";
        return 1;
    }


    /* get parameter with only longname */
    if( (cmdline.getparameter( name, "", "--name" )) != justargsOK )
    {
        std::cerr << "Parameter height not present or of wrong type!\n";
        return 1;
    }


    /* get parameter with both long and short names */
    if( (cmdline.getparameter( height, "-h", "--height" )) != justargsOK )
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