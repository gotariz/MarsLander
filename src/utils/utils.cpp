#include "utils.h"

template<typename T>
std::string toString( const T& value )
{
    std::ostringstream oss;
    try
    {
        // Turn on exceptions
        oss.exceptions( std::ios::badbit | std::ios::failbit );
        oss << value;
    }
    catch ( std::ios_base::failure e )
    {
        std::cerr << e.what() << std::endl;
        // clear the ostream
        oss.clear( std::ios::goodbit );
        return "";
    }
    return oss.str();
}

std::vector<std::string> splitString(std::string path, char delimeter)
{
    std::vector<std::string> result;
    std::string current_word = "";

    for(unsigned i = 0; i < path.length(); ++i)
    {
        char current_char = path.at(i);
        if (current_char != delimeter)
        {
            current_word.append( toString(current_char) );
        }

        if ( (current_char == delimeter) or (i == path.length() - 1)) //&& current_word != ""
        {
            result.push_back(current_word);
            current_word = "";
        }
    }

    return result;
}
