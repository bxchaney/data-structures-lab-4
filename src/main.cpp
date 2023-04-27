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
        file.get();
        std::cout << i << std::endl;
    }
    buff.close();
    return 0;

}

template <typename T>
class Foo
{
    private:
        template<typename U>
        class Box
        {
            public:
            U data;
            Box() = default;
            Box(U data) { this->data = data;}
        };

        std::shared_ptr<Box<T>> _box;

    public:
        Foo() = default;
        void make_box(T);
        T& inside_box();
};

template <typename T>
void Foo<T>::make_box(T data)
{
    _box = std::shared_ptr<Box<T>>(new Box(data));
}

template <typename T>
T& Foo<T>::inside_box()
{
    return _box->data;
}


int main(int argc, char* argv[])
{
    std::cout << argc << std::endl;
    std::cout << argv[1] << std::endl;

    Foo<int> f {};
    f.make_box(54);

    std::cout << f.inside_box() << std::endl;


    // if(argc < 2) {std::cout << "huh" << std::endl; return -1;}
    // std::filebuf input;
    // if (!input.open(argv[1], std::ios::in)) { return -1;}

    // std::istream is {&input};

    
    // char s [256];
    
    
    // while(!is.eof())
    // {
    //     is.getline(s, 256);
    //     std::cout << s << std::endl;
    //     if (open_and_read(s) == -1) 
    //     {
    //         input.close();
    //         return -1;
    //     }
    // }
    
}

