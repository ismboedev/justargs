# justargs  
> *just give me the arguments*


`justargs` gives you simple access to your command line arguments with just a single header file.  
It is pretty minimal and is not comparable to a solution with `Boost` or other more advanced command line parsers out in the wild. `justargs` is not really written with best programming conventions, but it just works.


## Simplest Example

An example says more than a thousand words (maybe).

```cpp
#include <iostream>
#include "justargs.h"

int main( int argc, char * argv[] )
{
    bool verbose;

    /* Contruct justargs class */
    justargs cmdline( argc, argv );

    /* get parameters from command line into variables */
    if( (cmdline.getparameter( verbose, "-v", "--verbose" )) != 0 )
    {
        std::cerr << "Parameter verbose not present or of wrong type!\n";
        return 1;
    }

    if( verbose )
        std::cout << "Yuup! Verbose it is!" << age << std::endl;
}
```

## Usage

Arguments have to be given with an equal sign in the form of:

```sh
$ ./simplest-example --verbose=true
```


## Tutorial

Create instance of justargs:

```cpp
justargs cmdline( argc, argv );
```

Get parameter values and write into predefined variables. This function is overloaded and accepts `bool`, `int`, `double` and `string` type variables as first argument.

```cpp
bool verbose;
if( (cmdline.getparameter( verbose, "-v", "--verbose" )) != 0 )
{
    std::cerr << "Not given or not boolen\n";
    return 1;
}
```



## Complete Example

```cpp
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
```