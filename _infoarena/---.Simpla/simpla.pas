var a,b:int64;

function rezolva(x:int64):int64;
var x1,x2,t:int64;
    sum,i:longint;
begin
  x1 := (x div 10)*10;
  x2 := x mod 10;

  sum := 0; t := x1 div 10; x1 := x1 div 2;
  while t <> 0 do
  begin
    sum := sum + t mod 10;
    t := t div 10;
  end;

  sum := sum mod 2;

  for i := 0 to x2 do
  begin
    if (sum + i) mod 2 = 0 then
      inc(x1);
  end;
  rezolva := x1;
end;

begin
  assign(input,'simpla.in'); reset(input);
  assign(output,'simpla.out'); rewrite(output);

  readln(a,b);

  //writeln(rezolva(b));
  //writeln(rezolva(a-1));

  writeln(rezolva(b)-rezolva(a-1));

  close(input);
  close(output);
end.
