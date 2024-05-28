int f(int a) {
  a = a + 1;
  return a + 5;
}

void main(void) { // Main function
  int a = 1;
  a = f(2);
  int b = a + 3;
  print(a); // Print 2+6=8
  print(b); // Print 8+3=11
}
