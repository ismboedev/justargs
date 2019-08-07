#include <string>
#include <vector>
#include <iostream>


/* simplest argument parser with boolean and parameter type of arguments */
class justargs
{
private:

    /* Vector with all arguments */
    std::vector<std::string> arguments;

    /* vector with just the names before the equal sign */
    std::vector<std::string> namesinput;

    /* vector with just the values after the equal sign */
    std::vector<std::string> valuesinput;

    /* define no value variable */
    std::string NOVALUE = "NO_VALUE";

    /* help information */
    std::string helpinfo;

    
public:
    /* Constructor */
    justargs( int argc, char * argv[] );

    ~justargs();

    /* get parameter, if they exist and convert to bool, int, double or string */
    int getparameter( bool& param, std::string shortname, std::string longname );
    int getparameter( int& param, std::string shortname, std::string longname );
    int getparameter( double& param, std::string shortname, std::string longname );
    int getparameter( std::string& param, std::string shortname, std::string longname );

    /* add general information to help */
    void addgeneral2help( std::string description );

    /* add parameters to help list */
    void addparam2help( std::string shortname, std::string longname, std::string description );

    /* print helpfinfo */
    void printhelp( void );

    /* for debugging purposes */
    void listargs();
};




justargs::justargs( int argc, char * argv[] )
{
    // get argumets
    for( int i = 1; i < argc; i++ )
    {
        arguments.push_back( argv[i] );
    }

    // extract names and values from arguments
    std::size_t posdelim = 0;
    for( int i = 0; i < arguments.size(); i++ )
    {
        posdelim = arguments[i].find( "=" );
        if( posdelim != std::string::npos )
        {
            namesinput.push_back( arguments[i].substr(0, posdelim ) );
            valuesinput.push_back( arguments[i].substr( posdelim + 1 ) );
        }
        else
        {
            namesinput.push_back( arguments[i] );
            valuesinput.push_back( NOVALUE );
        }
    }
    
}

justargs::~justargs()
{
}



void justargs::addgeneral2help( std::string description )
{
    helpinfo.append( description );
}


void justargs::addparam2help( std::string shortname, std::string longname, std::string description )
{
    helpinfo.append( " " );
    if( shortname == "" )
    {
        helpinfo.append( longname );
    }
    else if( longname == "" )
    {
        helpinfo.append( shortname ); //helpinfo.append( "\t" );
    }
    else if( (shortname != "") && (longname != "") )
    {
        helpinfo.append( shortname ); helpinfo.append( ", " ); helpinfo.append( longname );
    }

    if( (shortname+longname).length() <= 6  )
    {
        helpinfo.append( "\t\t\t" ); helpinfo.append( description ); helpinfo.append( "\n" );
    }
    else if( ( (shortname+longname).length() > 7 ) && ( (shortname+longname).length() <= 14 ) )
    {
        helpinfo.append( "\t\t" ); helpinfo.append( description ); helpinfo.append( "\n" );
    }
    else if( ( (shortname+longname).length() > 14 ) && ( (shortname+longname).length() <= 20 ) )
    {
        helpinfo.append( "\t" ); helpinfo.append( description ); helpinfo.append( "\n" );
    }
    else if( (shortname+longname).length() > 20 )
    {
        helpinfo.append( "\n\t\t\t" ); helpinfo.append( description ); helpinfo.append( "\n" );
    }
}


void justargs::printhelp( void )
{
    std::cout << helpinfo << std::endl;
}



/* get parameter as bool */
int justargs::getparameter( bool& param, std::string shortname, std::string longname )
{
    for( int i = 0; i < namesinput.size(); i++ )
    {
        if( ( ( namesinput[i] == shortname ) || ( namesinput[i] == longname ) ) && ( valuesinput[i] != NOVALUE ) )
        {

            // check if string says true
            if( ( valuesinput[i] == "true" ) || ( valuesinput[i] == "True" ) || ( valuesinput[i] ==" TRUE" ) )
            {
                param = true;
                return 0;
            }
            else
            {
                param = false;
                return 0;
            }
        }
    }
    // else parameter not found, or wrong type:
    return 2;
}

/* get parameter as int */
int justargs::getparameter( int& param, std::string shortname, std::string longname )
{
    for( int i = 0; i < namesinput.size(); i++ )
    {
        if( ( ( namesinput[i] == shortname ) || ( namesinput[i] == longname ) ) && ( valuesinput[i] != NOVALUE ) )
        {
            try
            {
                param = std::stoi( valuesinput[i] );
                return 0;
            }
            catch(const std::exception& e)
            {
                return 1;
            }
        }
    }
    // else parameter not found, or wrong type:
    return 2;
}

/* get parameter as double */
int justargs::getparameter( double& param, std::string shortname, std::string longname )
{
    for( int i = 0; i < namesinput.size(); i++ )
    {
        if( ( ( namesinput[i] == shortname ) || ( namesinput[i] == longname ) ) && ( valuesinput[i] != NOVALUE ) )
        {
            try
            {
                param = std::stod( valuesinput[i] );
                return 0;
            }
            catch(const std::exception& e)
            {
                return 1;
            }
        }
    }
    // else parameter not found, or wrong type:
    return 2;
}

/* get parameter as string */
int justargs::getparameter( std::string& param, std::string shortname, std::string longname )
{
    for( int i = 0; i < namesinput.size(); i++ )
    {
        if( ( ( namesinput[i] == shortname ) || ( namesinput[i] == longname ) ) && ( valuesinput[i] != NOVALUE ) )
        {
            param = valuesinput[i];
            return 0;
        }
    }
    // else parameter not found, or wrong type:
    return 2;
}





/* debug */
void justargs::listargs()
{
    std::cout << "number of args=" << arguments.size() << std::endl;

    for( int i = 0; i < arguments.size(); i++ )
    {
        std::cout << "arg" << i << " : " << arguments[i] << std::endl;
        std::cout << "name" << i << " : " << namesinput[i] << std::endl;
        std::cout << "value" << i << " : " << valuesinput[i] << std::endl;
    }

}