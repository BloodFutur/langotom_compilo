void main(void) { // Main function
  int a;
  a = 123 + 321 * 4 / 2 - 1; // a = 123 + 321 * 4 / 2 - 1 = 764
  if (a == 1) {
    print(a);
  } else {
    print(a - 1); // print(763)
    int i, j;
    i = 2;
    j = a - 10; // j = 764 - 10 = 754
    while (i < j) {
      i = i + 1 + 0 + 0;
      int k;
      print(i); // print(3), print(4), ..., print(754)
    }
  }
  print(1);
}
