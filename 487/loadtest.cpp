#include <iostream>
#include <thread>
using namespace std;

void func_dummy(int N)
 {
   for (int i = 0; i < N; i++) {
   cout << "Thread 1 :: callable => function pointer\n";
   }
 }
 
class thread_obj {
 public:
   void operator()(int n) {
       for (int i = 0; i < n; i++)
           cout << "Thread 2 :: callable => function object\n";
   }
};
 
int main()
{
auto f = [](int n) {
   for (int i = 0; i < n; i++)
   cout << "Thread 3 :: callable => lambda expression\n";
   };
thread th1(func_dummy, 2);
 
thread th2(thread_obj(), 2);
 
thread th3(f, 2);
 
 th1.join();
th2.join();
 
th3.join();
 
return 0;
}
