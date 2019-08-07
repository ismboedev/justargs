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


    /* Create help */
    cmdline.addgeneral2help( "Personal Information Display 0.1.5\n");
    cmdline.addgeneral2help( "\nThis application displays your Information from the command line arguments. All options are required!\n" );

    cmdline.addgeneral2help( "\nOptions:\n" );
    cmdline.addparam2help( "-v", "--verbose", "Set this true to get also the height displayed" );
    cmdline.addparam2help( "", "--name", "What is your name?" );
    cmdline.addparam2help( "-a", "", "How old are you?" );
    cmdline.addparam2help( "-h", "--height", "How tall are you?" );


    /* get parameters from command line into variables */
    if( (cmdline.getparameter( verbose, "-v", "--verbose" )) != 0 )
    {
        std::cerr << "Parameter verbose not present or of wrong type!\n";
        cmdline.printhelp();
        return 1;
    }


    /* get parameter with only shortname */
    if( (cmdline.getparameter( age, "-a", "" )) != 0 )
    {
        std::cerr << "Parameter age not present or of wrong type!\n";
        cmdline.printhelp();
        return 1;
    }


    /* get parameter with only longname */
    if( (cmdline.getparameter( name, "", "--name" )) != 0 )
    {
        std::cerr << "Parameter height not present or of wrong type!\n";
        cmdline.printhelp();
        return 1;
    }


    /* get parameter with both long and short names */
    if( (cmdline.getparameter( height, "-h", "--height" )) != 0 )
    {
        std::cerr << "Parameter height not present or of wrong type!\n";
        cmdline.printhelp();
        return 1;
    }

    
    std::cout << "Information given is:\n";
    std::cout << " Name: " << name << std::endl;
    std::cout << " Age: " << age << std::endl;
    if( verbose )
        std::cout << " Height: " << height << std::endl;


    return 0;
}