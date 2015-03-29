var n:longint;

begin
  assign(input,'iunie.in'); reset(input);
  assign(output,'iunie.out'); rewrite(output);

  readln(n);
  if n mod 2 = 0 then
    writeln(n div 4)
  else
    writeln(0);

  close(input);
  close(output);
end.