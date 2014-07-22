
#include <iostream>
#include <cstring>

using namespace std;

#define ROWS 5
#define COLS 6
int colors[ROWS][COLS] = {{1, 2, 1, 1, 2, 1},
   {2, 2, 1, 1, 2, 1},
   {1, 2, 2, 2, 1, 2},
   {1, 2, 2, 2, 1, 2},
   {1, 2, 1, 1, 2, 2}};

static void
change_to_color(int i, int j, int old, int n)
{
   if(i < 0)
      return;
   if(j < 0)
      return;
   if(i >= ROWS)
      return;
   if(j >= COLS)
      return;

   if(colors[i][j] == old) {
      colors[i][j] = n;
      change_to_color(i + 1, j, old, n); // down
      change_to_color(i, j -1, old, n); // left
      change_to_color(i - 1, j, old, n); // up
      change_to_color(i, j + 1, old, n); // right
   }
}

static void
paint(const int i, const int j, const int color)
{
   int old_color = colors[i][j];

   change_to_color(i, j, old_color, color);
}

int keyboard[6][5] = {{'a', 'b', 'c', 'd', 'e'},
                      {'f', 'g', 'h', 'i', 'j'},
                      {'k', 'l', 'm', 'n', 'o'},
                      {'p', 'q', 'r', 's', 't'},
                      {'u', 'v', 'w', 'x', 'y'},
                      {'z', ' ', ' ', ' ', ' '}};

static void
findSequence(char *word)
{
   size_t len = strlen(word);
   int row = 0, col = 0;

   for(size_t i(0); i < len; ++i) {
      char next = word[i];
      char target = next;
      bool isZ = (next == 'z');
      if(isZ && row != 5) {
         target = 'u';
      }
      int target_row = (target - 'a') / 5;
      int target_col = (target - 'a') % 5;

      if(row == 5 && !isZ) {
         // go up z
         cout << "up" << endl;
         row--;
      }
      if(row > target_row) {
         while(row != target_row) {
            cout << "up" << endl;
            row--;
         }
      } else if(row < target_row) {
         while(row != target_row) {
            cout << "down" << endl;
            row++;
         }
      }
      // go to col
      if(col > target_col) {
         while(col != target_col) {
            cout << "left" << endl;
            col--;
         }
      } else if(col < target_col) {
         while(col != target_col) {
            cout << "right" << endl;
            col++;
         }
      }
      if(isZ && row != 5) {
         cout << "down" << endl;
         ++row;
      }
      cout << "!" << endl;
   }
}

int
main(int argc, char **argv)
{
   for(size_t i(0); i < ROWS; ++i) {
      for(size_t j(0); j < COLS; ++j) {
         cout << colors[i][j];
      }
      cout << endl;
   }
   paint(1, 1, 1);
   cout << "==========" << endl;
   for(size_t i(0); i < ROWS; ++i) {
      for(size_t j(0); j < COLS; ++j) {
         cout << colors[i][j];
      }
      cout << endl;
   }
   findSequence("zzzzabcdefghijklmnopqrstuvxz");
   return 0;
}
