main(n){
  i = 0;
  j = 1;
  k = 0;
  while(k < n){
    tmp = i + j;
    i = j;
    j = tmp;
    k = k + 1;
  }
  return i;
}
