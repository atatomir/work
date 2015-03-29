const modd = 1999999973;
var n,k:int64;

function poww(n,k:int64):int64;
begin
  if k = 0 then poww := 0 else
  if k = 1 then poww := n else
  begin
    if k mod 2 = 1 then
      poww := (n*poww((n*n)mod modd,k div 2))mod modd
    else
      poww :=   (poww((n*n)mod modd,k div 2))mod modd;
  end;
end;

begin
  assign(input,'lgput.in'); reset(input);
  assign(output,'lgput.out'); rewrite(output);

  readln(n,k);
  writeln(poww(n,k));

  close(input);
  close(output);
end.