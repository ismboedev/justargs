#include <string>
#include <vector>
#include <iostream>

/* define return types */
#define justargsOK 0
#define justargsPRESENT 1
#define justargsFAIL 2
#define justargsNOTFOUND 3


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

    
public:
    /* Constructor */
    justargs( int argc, char * argv[] );

    ~justargs();

    /* get parameter, if they exist and convert to bool, int, double or string */
    int getparameter( bool& param, std::string shortname, std::string longname );
    int getparameter( int& param, std::string shortname, std::string longname );
    int getparameter( unsigned int& param, std::string shortname, std::string longname );
    int getparameter( double& param, std::string shortname, std::string longname );
    int getparameter( std::string& param, std::string shortname, std::string longname );

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




/* get parameter as bool */
int justargs::getparameter( bool& param, std::string shortname, std::string longname )
{
    for( int i = 0; i < namesinput.size(); i++ )
    {
        if( ( namesinput[i] == shortname ) || ( namesinput[i] == longname ) )
        {
            if( valuesinput[i] != NOVALUE )
            {
                // check if string says true
                if( ( valuesinput[i] == "true" ) || ( valuesinput[i] == "True" ) || ( valuesinput[i] ==" TRUE" ) )
                {
                    param = true;
                    return justargsOK;
                }
                else
                {
                    param = false;
                    return justargsOK;
                }
            }
            return justargsPRESENT;
        }
    }
    // else parameter not found, or wrong type:
    return justargsNOTFOUND;
}

/* get parameter as int */
int justargs::getparameter( int& param, std::string shortname, std::string longname )
{
    for( int i = 0; i < namesinput.size(); i++ )
    {
        if( ( namesinput[i] == shortname ) || ( namesinput[i] == longname )  )
        {
            if( valuesinput[i] != NOVALUE )
            {
                try
                {
                    param = std::stoi( valuesinput[i] );
                    return justargsOK;
                }
                catch(const std::exception& e)
                {
                    return justargsFAIL;
                }
            }
            return justargsPRESENT;
        }
    }
    // else parameter not found, or wrong type:
    return justargsNOTFOUND;
}

/* get parameter as unsigned int */
int justargs::getparameter( unsigned int& param, std::string shortname, std::string longname )
{
    for( int i = 0; i < namesinput.size(); i++ )
    {
        if( ( namesinput[i] == shortname ) || ( namesinput[i] == longname )  )
        {
            if( valuesinput[i] != NOVALUE )
            {
                try
                {
                    param = std::stoul( valuesinput[i] );
                    return justargsOK;
                }
                catch(const std::exception& e)
                {
                    return justargsFAIL;
                }
            }
            return justargsPRESENT;
        }
    }
    // else parameter not found, or wrong type:
    return justargsNOTFOUND;
}

/* get parameter as double */
int justargs::getparameter( double& param, std::string shortname, std::string longname )
{
    for( int i = 0; i < namesinput.size(); i++ )
    {
        if( ( namesinput[i] == shortname ) || ( namesinput[i] == longname )  )
        {
            if( valuesinput[i] != NOVALUE )
            {
                try
                {
                    param = std::stod( valuesinput[i] );
                    return justargsOK;
                }
                catch(const std::exception& e)
                {
                    return justargsFAIL;
                }
            }
            return justargsPRESENT;
        }
    }
    // else parameter not found, or wrong type:
    return justargsNOTFOUND;
}

/* get parameter as string */
int justargs::getparameter( std::string& param, std::string shortname, std::string longname )
{
    for( int i = 0; i < namesinput.size(); i++ )
    {
        if( ( namesinput[i] == shortname ) || ( namesinput[i] == longname )  )
        {
            if( valuesinput[i] != NOVALUE )
            {
                param = valuesinput[i];
                return justargsOK;
            }
            return justargsPRESENT;
        }
    }
    // else parameter not found, or wrong type:
    return justargsNOTFOUND;
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