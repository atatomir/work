var a:array[1..5001]of longint;
    n,i,e,p:longint;

procedure qsort(l,r:longint);
var  i,j,m,y:longint;
begin
  i := l; j := r; m := a[(l+r)div 2];
  repeat
    while a[i] < m do inc(i);
    while a[j] > m do dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if i < r then  qsort(i,r);
  if j > l then  qsort(l,j);
end;

function cautare_binara(x:longint):longint;
var m,u,v:longint;
begin
  u := 1 ; v := n; cautare_binara := 0;
  repeat
    m := (u+v) div 2;
    if x < a[m] then
      v := m-1
    else
      u := m+1;
  until u > v;

  cautare_binara := v;
end;


begin
  assign(input,'binsort.in'); reset(input);
  assign(output,'binsort.out'); rewrite(output);

  readln(n);
  for i := 1 to n do read(a[i]);
  readln(p);

  qsort(1,n);

  for i := 1 to p do
  begin
    readln(e);
    writeln(e,' ',cautare_binara(e));
  end;





  for i := 1 to n do write(a[i],' '); writeln();

  close(input);
  close(output);
end.
