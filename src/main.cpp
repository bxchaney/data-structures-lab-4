#include<iostream>
#include<filesystem>
#include<fstream>
#include<memory>
#include<string>
#include"sorting/utils/queue.h"
#include"sorting/qsort.h"

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
    Queue<int> q {};
    while (!file.eof())
    {
        file >> i;
        file.get();
        q.enqueue(i);
        
    }
    std::cout << "Queue filled" << std::endl;
    QuickSort qsort {q, 3};
    qsort.sort();
    std::cout << qsort << std::endl;
   // qsort.write_output(std::cout);
    buff.close();
    return 0;

}


int main(int argc, char* argv[])
{
    // std::cout << argc << std::endl;
    // std::cout << argv[1] << std::endl;

    // std::cout << f.inside_box() << std::endl;


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

