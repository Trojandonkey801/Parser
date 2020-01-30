#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
using namespace std;
int main(int argc, char* argv[])
{
   const int NUM_ELEMENTS = 5000000;
   int clicks, lc, curr;
   float secs;
   vector<int> vec;
   auto t1 = std::chrono::high_resolution_clock::now();

   // Push values to vector
   for(lc = 0; lc < NUM_ELEMENTS; lc++)
   {
      vec.push_back(lc);
   } // for

   // Access and assignment (using [] operator)
   for(lc = 0; lc < NUM_ELEMENTS; lc++)
   {
      curr = vec[lc];
   } // for

   clicks = clock();
   secs   = ((float)clicks)/CLOCKS_PER_SEC;
   auto t2 = std::chrono::high_resolution_clock::now();
   cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << endl;
   return 0;
} // main 
