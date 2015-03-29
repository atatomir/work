var n,i:longint;
    f1,f2,y1,y2,x1,x2,s:extended;

function formula:real;
begin
  formula := x1*y2-x2*y1;
end;

begin
  assign(input,'aria.in'); reset(input);
  assign(output,'aria.out'); rewrite(Output);

  readln(n);  s := 0;
  readln(f1,f2);
  x1 := f1; y1 := f2;

  for i := 2 to n do
  begin
    readln(x2,y2);
    s := s + formula ;
    x1 := x2;
    y1 := y2;
  end;

  x2 := f1; y2 := f2;
  s := s + formula ;

  s := s/2;
  writeln(s:0:6);

  close(input);
  close(output);
end.
