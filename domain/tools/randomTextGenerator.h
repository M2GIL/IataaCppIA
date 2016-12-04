#ifndef CHECKERS_REST_IA_C_RANDOMTEXTGENERATOR_H
#define CHECKERS_REST_IA_C_RANDOMTEXTGENERATOR_H

#include <string>
#include <cstdlib>
#include <ctime>

using std::string;
using std::time;
using std::srand;
using std::size_t;

class randomTextGenerator
{
public:
    static randomTextGenerator& getInstance()
    {
        static randomTextGenerator instance;
        return instance;
    }

public:
    randomTextGenerator(const string& str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
            : m_str(str)
    {
        srand(time(NULL));
    }

    randomTextGenerator(randomTextGenerator const&) = delete;
    void operator=(randomTextGenerator const&) = delete;
    
    string operator()(size_t len = 1)
    {
        string seq;
        size_t siz = m_str.size();
        if(siz)
            while(len--)
                seq.push_back(m_str[rand() % siz]);
        return seq;
    }
    
private:
    string m_str;
};


#endif
