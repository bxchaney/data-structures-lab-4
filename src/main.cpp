#include<iostream>
#include<filesystem>
#include<fstream>
#include<memory>
#include<string>
#include"sorting/utils/queue.h"
#include"sorting/qsort.h"
#include"sorting/mergesort.h"

namespace fs = std::filesystem;

/// @brief writes the mergesort output to a file and writes summary information
/// to the console.
/// @param input_file the name of the input file.
/// @param natl_merge natural merge object containing sorted data.
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
    if(!merge_buff.open(p, std::ios::out))
    {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }
    std::ostream os {&merge_buff};
    natl_merge.write_output(os);
    merge_buff.close();
}

/// @brief writes the quicksort output to a file and writes summary information
/// to the console.
/// @param input_file 
/// @param qsort 
/// @param type 
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
    if(!qsort_buff.open(p, std::ios::out))
    {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }
    std::ostream os {&qsort_buff};
    qsort.write_output(os);
    qsort_buff.close();
}

void run_sorting_algorithms(Queue<int>& q, char* s, std::ostream& summary_os)
{
    std::string filename = fs::path(s).filename().string();
    NaturalMergeSort natl_merge {q};
    natl_merge.sort();
    std::cout << natl_merge << std::endl;
    summary_os << s << ",";
    natl_merge.write_summary(summary_os);
    write_merge_output(filename, natl_merge);

    for (int i = 0; i<= 3; i++)
    {
        QuickSort qsort {q, i};
        qsort.sort();
        std::cout << qsort << std::endl;
        summary_os << s << ",";
        qsort.write_summary(summary_os);
        write_qsort_output(filename, qsort, i);
    }
}

/// @brief opens and reads one of the filepaths in the input file. Triggers
/// all sorting algorithms.
/// @param s 
/// @param os 
/// @return 
int open_and_read(char* s, std::ostream& os)
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
    buff.close();
    run_sorting_algorithms(q, s, os);
    return 0;
}

/// @brief Writes the headers for the summary csv.
/// @param os 
void write_summary_headers(std::ostream& os)
{
    os << "Input File" << ",";
    os << "Type" << ",";
    os << "Partition Size" << ",";
    os << "Pivot Type" << ",";
    os << "Comparisons" << ",";
    os << "Exchanges" << std::endl;
}

int main(int argc, char* argv[])
{
    // Assumes the first argument is the input file.
    // Does not consider any other outputs.
    if(argc < 2) {std::cout << "huh" << std::endl; return -1;}
    std::filebuf input;
    if (!input.open(argv[1], std::ios::in)) { return -1;}

    std::istream is {&input};

    
    char s [256];
    std::filebuf summ_buff;
    fs::path p = fs::current_path();
    p /= "summary.csv";
    summ_buff.open(p, std::ios::out);  
    std::ostream os {&summ_buff};  
    write_summary_headers(os);
    while(!is.eof())
    {
        is.getline(s, 256);
        std::cout << "Input: " << s << std::endl;
        if (open_and_read(s, os) == -1) 
        {
            input.close();
            return -1;
        }
    }
    summ_buff.close();
}

