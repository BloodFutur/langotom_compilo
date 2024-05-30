int add(int a, int b) {
  return a+b;
}

int one(void) {
  return 1;
}

void printa(int a) {
  print(a);
}

int fact(int n) {
  if (n == 0) {
    return 1;
  } else {
    return n*fact(n-1);
  }
}

int inc(int n) {
  return n+1;
}

void main(void) { // Main function
  int a = 42;
  int b = 69;
  int c = add(a,b);
  int d = fact(6);
  int e = inc(42);
  print(c); // Print 42+69=111
  print(d); // Factorial of 6=720
  print(e);
  int f = one();
  int g = 0;
  print(f); // Print 1

  print(89);

}
