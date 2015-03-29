const a:array[1..12]of longint = (1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600);
var i,t,n:longint;
    r:array[1..12]of longint;

begin
  assign(input,'sumfact.in'); reset(input);
  assign(output,'sumfact.out'); rewrite(output);

  readln(n);
  for i := 12 downto 1 do
  begin
    r[i] := n div a[i];
    n := n mod a[i];
  end;

  i := 12;
  while r[i] = 0 do dec(i);

  writeln(i);
  for t := 1 to i do writeln(r[t]);



  close(input);
  close(output);
end.