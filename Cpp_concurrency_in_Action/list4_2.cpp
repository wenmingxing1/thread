#include<future>
#include<iostream>

using namespace std;

int find_the_answer_to_ltuar();
void do_other_stuff();

int main() {

    //Ҳ������async�д��ݲ���
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    cout << the_answer.get() << endl;

    return 0;
}
