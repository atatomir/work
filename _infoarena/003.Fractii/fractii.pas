var a:array[1..1000000]of longint;
    n,i,j,h:longint;
    nr:int64;

begin
  assign(input,'fractii.in'); reset(input);
  assign(output,'fractii.out'); rewrite(output);

  readln(n);
  nr := 1 ;
  for i := 2 to n do a[i] := i-1;

  for i := 2 to n do
  begin
    nr := nr + 2*a[i];
    h := n div i;
    for j := 2 to h do a[i*j] := a[i*j] - a[i];
  end;

  writeln(nr);

  close(input);
  close(output);
end.
