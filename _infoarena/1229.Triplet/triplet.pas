var n:longint;
    t:longint;

begin
  assign(input,'triplet.in'); reset(input);
  assign(output,'triplet.out'); rewrite(output);

  readln(n);
  if n mod 2 = 0 then
  begin
    t := 1;
    n := n-1;
  end
  else
    t := 0;

  writeln(n div 2 + 1,' ',(-1)*(n div 2),' ',t);



  close(input);
  close(output);
end.