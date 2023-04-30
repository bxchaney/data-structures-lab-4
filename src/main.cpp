#include<iostream>
#include<filesystem>
#include<fstream>
#include<memory>
#include<string>
#include"sorting/utils/queue.h"
#include"sorting/qsort.h"
#include"sorting/mergesort.h"

namespace fs = std::filesystem;

void write_merge_output(std::string& input_file, NaturalMergeSort& natl_merge)
{
    std::filebuf merge_buff;
    fs::path p = fs::current_path();
    p /= "./out";
    if (!fs::exists(p))
    {
        fs::create_directory(p);
    }
    std::string filename = "merge_sorted_" + input_file;
    p /= filename;
    merge_buff.open(p, std::ios::out);
    std::ostream os {&merge_buff};
    natl_merge.write_output(os);
    merge_buff.close();
}

void write_qsort_output(std::string& input_file, QuickSort& qsort, int type)
{
    std::filebuf qsort_buff;
    fs::path p = fs::current_path();
    p /= "./out";
    if (!fs::exists(p))
    {
        fs::create_directory(p);
    }
    std::string detail;
    switch (type)
    {
        case 1:
            detail = "partition50_";
            break;
        case 2:
            detail = "partition100_";
            break;
        case 3:
            detail = "partition2_median_pivot_";
            break;
        default:
            detail = "partition2_first_pivot_";
    }
    std::string filename = detail + input_file;
    p /= filename;
    qsort_buff.open(p, std::ios::out);
    std::ostream os {&qsort_buff};
    qsort.write_output(os);
    qsort_buff.close();
}

void run_sorting_algorithms(Queue<int>& q, char* s)
{
    std::string filename = std::filesystem::path(s).filename();
    NaturalMergeSort natl_merge {q};
    natl_merge.sort();
    std::cout << natl_merge << std::endl;
    write_merge_output(filename, natl_merge);

    // for (int i = 0; i<= 3; i++)
    // {
    //     QuickSort qsort {q, i};
    //     qsort.sort();
    //     std::cout << qsort << std::endl;
    //     write_qsort_output(filename, qsort, i);
    // }
}

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
    run_sorting_algorithms(q, s);
    buff.close();
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

