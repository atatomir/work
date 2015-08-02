var x,s,fact,nr:longint;
    i,n:longint;

begin
  assign(input,'sumall.in'); reset(input);
  assign(output,'sumall.out'); rewrite(output);

  readln(x);
  n := 0; s := 0; fact := 1;

  while x <> 0 do
  begin
    s := s + x mod 10; x := x div 10;
    inc(n);
    if n > 2 then fact := fact * (n-1);
  end;


  nr := 1;
  for i := 2 to n do nr := nr*10 + 1;

  nr := fact*s*nr;

  writeln(nr);


  close(input);
  close(output);
end.