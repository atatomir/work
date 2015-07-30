const mod1 = 9001;
var n,i,j,m,t,s:longint;
    a:array[1..5001,1..10001] of smallint;

begin
  assign(input,'flori.in'); reset(input);
  assign(output,'flori.out'); rewrite(output);

  readln(n);
  m := (n+1) div 2;
  for i := 1 to n do a[1,i] := i;

  for i := 2 to m do
  begin
    t := (i-1)*2;
    for j := 1 to t do a[i,j] := 0;

    inc(t);
    for j := t to n do a[i,j] := (a[i,j-1] + a[i-1,j-2]) mod mod1;
  end;

  s := 0;
  for i := 1 to m do s := (s + a[i,n]) mod mod1;

  writeln(s);

  //for i := 1 to m do writeln(a[i,n-1],' ',a[i,n]);

  close(input);
  close(output);
end.
