
int
shift(int n)
{
   return (x << 1) | ((x & 0x80000000) >> 31);
}

int
main(void)
{
   int x = 2;

   shift(x);
}
