const modd=666013;
var n,p,q,start,stop,val,i,j:longint;
    a,b:array[0..1000005]of longint;

function rest(x:longint):longint;
begin
  rest := x;
  if rest < 0 then rest := rest + modd;
end;

begin
  assign(input,'unuzero.in'); reset(input);
  assign(output,'unuzero.out'); rewrite(output);

  read(n); n := n + 2;
  readln(p,q); inc(p); inc(q);

  b[0] := 0;

  for i := 1 to n do
  begin
    start := i - q; if start <= 0 then start := 1;
    stop  := i - p;

    val := a[i-1];
    {for j := start to stop do
      val := (val+a[j]+1)mod modd; }

    if stop >= start then val := (val + rest(b[stop] - b[start-1]) + stop-start+1)mod modd;

    a[i] := val;
    b[i] := (b[i-1] + val)mod modd;

  end;

  writeln(a[n]);


  close(input);
  close(output);
end.
