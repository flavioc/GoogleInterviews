
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

static char*
rotate_string(char *s, int k)
{
   size_t len = strlen(s);
   k = k % len;
   char temp[k];
   strncpy(temp, s, k);
   memmove(s, s + k, len - k);
   strncpy(s + (len - k), temp, k);

   return s;
}

static void
reverse_string(char *x, int n)
{
   char *s = x;
   char *e = x + n - 1;

   while(s < e) {
      char tmp = *s;
      *s = *e;
      *e = tmp;
      s++;
      e--;
   }
}

static char*
rotate_in_place(char *s, int k)
{
   int len = strlen(s);

   reverse_string(s, len);
   reverse_string(s + (len - k), k);
   reverse_string(s, len - k);
   return s;
}

static char*
rotate_left(char *s, int k)
{
   int len = strlen(s);

   reverse_string(s, len);
   reverse_string(s, k);
   reverse_string(s + k, len - k);
   return s;
}

static string
ordinal_excel(int n)
{
   string s;
   while(n > 0) {
      char x = 'A' + ((n-1)%26);

      s += x;
      n = (n-1) / 26;
   }
   reverse(s.begin(), s.end());
   cout << s << endl;
   return s;
}

static string
compress_string(char *s)
{
   string ret;
   for(int i = 0; s[i]; ++i) {
      int n = 1;
      while(s[i] == s[i+1]) {
         i++;
         n++;
      }
      printf("%c%d", s[i], n);
   }
   cout << endl;
   return string();
}

static void
reverse(char *s, int r)
{
   int l = 0;

   while(l < r) {
      swap(s[l], s[r]);
      l++;
      r--;
   }
}

static void
reverseWords(char *s)
{
   for(int i(0); s[i]; ++i) {
      if(isalpha(s[i])) {
         int start = i;
         int len = 1;
         while(s[i+1] && isalpha(s[i+1])) {
            i++;
            len++;
         }
         reverse(s + start, len - 1);
      }
   }
   cout << s << endl;
}

static void
doPermutations(char *s, int j, int len, char *counts)
{
   if(j == len) {
      cout << s << endl;
      return;
   }

   for(size_t i(0); i < 26; ++i) {
      if(counts[i] > 0) {
         counts[i]--;
         s[j] = 'a' + i;
         doPermutations(s, j + 1, len, counts);
         counts[i]++;
      }
   }
}

static void
permutations(char *s, int len)
{
   char count[26];
   for(size_t i(0); i < 26; ++i)
      count[i] = 0;

   for(size_t i(0); i < len; ++i) {
      count[s[i] - 'a']++;
   }

   doPermutations(s, 0, len, count);
}

static string
longest_common_prefix(const vector<string>& vec)
{
   string ret;
   if(vec.empty())
      return ret;

   int j = 0; // next item to test

   while(true) {
      char c = vec[0][j];
      bool all_ok = true;
      for(size_t i(1); i < vec.size(); ++i) {
         if(vec[i][j] != c) {
            all_ok = false;
            break;
         }
      }

      if(all_ok) {
         ret += c;
         j++;
      } else
         break;
   }
   return ret;
}

static int
find_index(const char *big, vector<string>& strs, const char *word, size_t pos_in_vec)
{
   if(strs.empty())
      return - 1;
   size_t len(strlen(word));
   size_t longest_prefix;
   size_t i, j;
   bool first = true;

   // find longest in others
   for(i = 0; i < strs.size(); ++i) {
      if(i == pos_in_vec)
         continue;

      for(j = 0; j < len; ++j) {
         if(word[j] != strs[i][j])
            break;
      }
      if(first || j > longest_prefix) {
         first = false;
         longest_prefix = j;
      }
   }

   if(first) {
      return 0;
   }

   longest_prefix++; // need to check the extra char

   size_t big_len = strlen(big);
   for(i = 0; i < big_len; i += len) {
      bool found = true;
      for(j = 0; j < longest_prefix; ++j) {
         if(word[j] != big[i + j]) {
            found = false;
            break;
         }
      }
      if(found)
         return i;
   }

   return -1;
}

static bool
isPrime(int num)
{
   if(num < 2)
      return false;
   if(num == 2)
      return true;
   for(int i(2); i*i <= num; ++i) {
      if(num % i == 0)
         return false;
   }
   return true;
}

static void
checkPrime(int *num, int low, int high)
{
   int total = 0;
   for(; low <= high; ++low) {
      total *= 10;
      total += num[low];
   }
   if(isPrime(total)) {
      cout << total << endl;
   }
}

static void
findPrimesInNumbers(int *num, int i, int size, int total)
{
   for(size_t i(0); i < size; ++i) {
      for(size_t j(i); j < size; ++j) {
         checkPrime(num, i, j);
      }
   }
}

static void
findPrimes(char *str)
{
   size_t len = strlen(str);
   int numbers[len];

   for(size_t i(0); i < len; ++i) {
      if(isdigit(str[i])) {
         int j = 0;
         numbers[j++] = str[i]-'0';
         while(isdigit(str[i+1])) {
            i++;
            numbers[j++] = str[i]-'0';
         }
         findPrimesInNumbers(numbers, 0, j, 0);
      }
   }
}

static void
addBytes(char *a, char *b)
{
   size_t la = strlen(a);
   size_t lb = strlen(b);
   char c[max(la, lb) + 2];

   int cc = 0;
   int aa = la-1;
   int bb = lb-1;
   int carry = 0;
   char d;

   while(aa >= 0 || bb >= 0) {
      d = carry;
      if(aa >= 0) {
         d += a[aa] - '0';
         aa--;
      }
      if(bb >= 0) {
         d += b[bb] - '0';
         bb--;
      }
      if(d > 1) {
         d %= 2;
         carry = 1;
      } else
         carry = 0;

      c[cc++] = (d + '0');
   }
   if(carry)
      c[cc++] = '1';
   reverse(c, c + cc);
   c[cc] = '\0';
   cout << c << endl;

}

static void
reverse_order_words(char *str)
{
   int len = strlen(str);

   reverse_string(str, len);

   for(size_t i(0); i < len; ++i) {
      if(isalpha(str[i])) {
         int start = i;
         while(isalpha(str[i+1])) {
            i++;
         }
         reverse_string(str + start, i - start + 1);
      }
   }

   cout << str << endl;
}

static void
multiply_strings(char *a, char *b)
{
   size_t la = strlen(a);
   size_t lb = strlen(b);
   char out[la + lb + 1];

   for(size_t i(0); i < la + lb; ++i)
      out[i] = '0';
   out[la + lb] = '\0';

   int carry = 0;
   int pb = lb - 1;
   int pc = la + lb - 1;

   while(pb >= 0) {
      int nb = b[pb] - '0';
      int startpc = pc;
      for(int pa = la - 1; pa >= 0; --pa) {
         int na = a[pa] - '0';
         int nc = out[pc] - '0';
         int result = na * nb + carry + nc;
         carry = result / 10;
         result %= 10;
         out[pc] = result + '0';
         pc--;
      }
      out[pc] = carry + '0';
      carry = 0;

      pb--;
      pc = startpc - 1;
   }
   cout << out << endl;
}

static bool
regexp(char *str, char *pattern, int pos_str, int pos_pattern, int len_str, int len_pattern)
{
   if(pos_str == len_str) {
      for(; pos_pattern < len_pattern; ++pos_pattern)
         if(pattern[pos_pattern] != '*')
            return false;
      return true;
   }
   if(pos_pattern == len_pattern)
      return false;

   if(pattern[pos_pattern] == '?')
      return regexp(str, pattern, pos_str+1, pos_pattern+1, len_str, len_pattern);
   else if(pattern[pos_pattern] == '*') {
      for(int i = pos_str; i < len_str; ++i) {
         if(regexp(str, pattern, i, pos_pattern + 1, len_str, len_pattern))
            return true;
      }
   } else if(pattern[pos_pattern] == '+') {
      for(int i = pos_str + 1; i < len_str; ++i) {
         if(regexp(str, pattern, i, pos_pattern + 1, len_str, len_pattern))
            return true;
      }
   } else if(pattern[pos_pattern] == str[pos_str]) {
      return regexp(str, pattern, pos_str + 1, pos_pattern + 1, len_str, len_pattern);
   } else
      return false;
}

static bool
checkRegexp(char *str, char *pattern)
{
   return regexp(str, pattern, 0, 0, strlen(str), strlen(pattern));
}

int
main(int argc, char **argv)
{
   char s[] = "abcd";
   cout << rotate_string(s, 2) << endl; 
   cout << rotate_in_place(s, 2) << endl; 
   cout << rotate_left(s, 2) << endl; 
   ordinal_excel(1);
   ordinal_excel(3);
   ordinal_excel(26);
   ordinal_excel(27);
   ordinal_excel(28);
   compress_string("asfdssf");
   char a[] = "abc flavio yah yah";
   reverseWords(a);
   char f[] = "flavio";
   permutations(f, 6);
   vector<string> strs;
   strs.push_back("flavio");
   strs.push_back("flaA");
   strs.push_back("flxA");
   cout << longest_common_prefix(strs) << endl;
   strs.clear();
   strs.push_back("flavio");
   strs.push_back("flacio");
   strs.push_back("favoni");
   cout << find_index("flavioflaciofavoni", strs, "flacio", 1) << endl;
   char *primes = "abc2134kd31";
   cout << "PRIMES" << endl;
   findPrimes(primes);
   addBytes("0110", "1010");
   char hello[] = "Hello World";
   reverse_order_words(hello);
   multiply_strings("50", "12");
   return 0;
}
