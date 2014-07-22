
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

static vector<string>
decode(const string& s)
{
   if(s.length() == 0) {
      vector<string> vec;
      vec.push_back("");
      vec.push_back("");
      return vec;
   }

   vector<string> v;
   for(int try_assumed = 0; try_assumed <= 1; ++try_assumed) {
      string acc = "";
      int last = 0;
      bool failed = false;
      int assumed = try_assumed;
      for(size_t i(0); i < s.size(); ++i) {
         char c;
         c = s[i];

         if(c == '0') {
            if(assumed > 0 || last > 0) {
               v.push_back("NONE");
               failed = true;
               break;
            }
            acc += "0";
            last = 0;
            assumed = 0;
         } else if(c == '1') {
            if(assumed == 1 && last == 1) {
               v.push_back("NONE");
               failed = true;
               break;
            } else if(assumed == 0 && last == 0) {
               acc += "0";
               last = 0;
               assumed = 1;
            } else if(assumed == 1 && last == 0) {
               acc += "1";
               last = 1;
               assumed = 0;
            } else if(assumed == 0 && last == 1) {
               acc += "0";
               last = 0;
               assumed = 0;
            } else {
            }
         } else if(c == '2') {
            if(last == 0 && assumed == 0) {
               v.push_back("NONE");
               failed = true;
               break;
            } else if(last == 1 && assumed == 0) {
               acc += "0";
               last = 0;
               assumed = 1;
            } else if(last == 0 && assumed == 1) {
               acc += "1";
               last = 1;
               assumed = 1;
            } else if(last == 1 && assumed == 1) {
               acc += "1";
               last = 1;
               assumed = 0;
            } else {
            }
         } else if(c == '3') {
            if(assumed == 0 || last == 0) {
               v.push_back("NONE");
               failed = true;
               break;
            } else {
               // both 1
               last = 1;
               assumed = 1;
               acc += "1";
            }
         }
      }
      if(!failed) {
         if(assumed == 1) {
            v.push_back("NONE");
         } else {
            v.push_back(acc);
         }
      }
   }
   return v;
}

int
main(int argc, char **argv)
{
   //string s = "123210122";
   string s = "3";
   //string s = "1";
   vector<string> vec(decode(s));
   cout << vec[0] << endl;
   cout << vec[1] << endl;
   return 0;
}
