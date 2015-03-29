var A,B,X,t:longint;
function cmmdc(x,y:longint):longint;
begin
  if x < 0 then x := -x;
  if x < y then begin t := x; x := y; y := t; end;
  while y <> 0 do
  begin
    x := x mod y;
    t := x; x := y; y := t;
  end;
  cmmdc := x;
end;

begin
  assign(input,'holiday.in'); reset(input);
  assign(output,'holiday.out'); rewrite(output);

  readln(A,B,x);
  A := A - B;
  writeln(cmmdc(A,x));

  close(input);
  close(output);
end.