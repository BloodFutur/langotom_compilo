int f(int a) {
  if (a == 0) {
    return 1;
  } else {
    return a * f(a - 1);
  }
}

void main(void) { // Main function
  int a = 1;
  a = f(6);
  int b = a + 3;
  print(a); // Print 2+6=8
  print(b); // Print 8+3=11
}
