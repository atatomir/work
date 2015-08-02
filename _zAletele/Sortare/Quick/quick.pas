var n,i:longint;
    a:array[1..500005]of longint;
    bufin,bufout:array[1..65000]of byte;

procedure QuickSort(l,r:longint);
var m,y,i,j:longint;
begin
  i := l; j := r; m := a[(l+r)div 2];
  repeat
    while a[i] < m do inc(i);
    while a[j] > m do dec(j);
    if i<=j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if i < r then QuickSort(i,r);
  if j > l then QuickSort(l,j);
end;


begin
  assign(input,'algsort.in'); reset(input);
  assign(output,'algsort.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 1 to n do read(a[i]);

  QuickSort(1,n);

  for i := 1 to n do write(a[i],' ');

  close(input);
  close(output);
end.
