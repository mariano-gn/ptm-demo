/**
Copyright (c) 2016 Mariano Gonzalez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <string>
#include <vector>

class A {
public:
    A(int val1, int val2) : data_member1(val1), data_member2(val2) {}
    
    void function_member() {
        std::cout << "Hello from A::function_member!" <<
            "\n\tMy data_member1 is: " << data_member1 <<
            "\n\tAnd my data_member2 is: " << data_member2 << std::endl;
    }

    int data_member1 = 0;
    int data_member2 = 1;
};

template<typename T, typename U>
void execute_on_object(T&& object, U&& method) {
    // Important: due to operators precedence,
    // you need to resolve first either "object.*method" or "object->*method" before actually calling the method.
    (object.*method)();
}

template<typename T, typename U>
void print_from_object(T&& object, U&& member) {
    std::cout << "Printing value from object: " << object.*member << std::endl;
}

int main() {
    // Initialize a vector of A's.
    std::vector<A> vec{ {1, 2}, {15, 3}, {5, 30}, {100, 10000} };

    // Grab the pointer to the function member and the 2 data members.
    auto pointer_to_fn_member = &A::function_member;
    auto pointer_to_fst_data_member = &A::data_member1;
    auto pointer_to_snd_data_member = &A::data_member2;

    std::cout << "Iterating to execute.\n";
    for (auto item : vec) {
        execute_on_object(item, pointer_to_fn_member);
    }

    std::cout << "Iterating to print the first value of each member.\n";
    for (auto item : vec) {
        print_from_object(item, pointer_to_fst_data_member);
    }

    std::cout << "Iterating to print the second value of each member.\n";
    for (auto item : vec) {
        print_from_object(item, pointer_to_snd_data_member);
    }
}
