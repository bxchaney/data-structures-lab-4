#include<iostream>
#include<fstream>
#include<memory>

int open_and_read(char* s)
{
    std::filebuf buff;
    if (!buff.open(s, std::ios::in))
    {
        std::cout << "error opening" << std::endl;
        return -1;
    }
    std::istream file {&buff};
    int i;
    while (!file.eof())
    {
        file >> i;
        std::cout << i << " " << file.eofbit << std::endl;
    }
    return 0;

}

int main(int argc, char* argv[])
{
    if(argc < 2) {std::cout << "huh" << std::endl; return -1;}
    std::filebuf input;
    if (!input.open(argv[1], std::ios::in)) { return -1;}

    std::istream is {&input};

    
    char s [256];
    
    
    while(!is.eof())
    {
        is.getline(s, 256);
        std::cout << s << std::endl;
        if (open_and_read(s) == -1) 
        {
            input.close();
            return -1;
        }
    }
    
}

