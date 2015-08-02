uses crt,sysutils;

var s,t:int64;
    n,i:byte;

begin
  clrscr;
  readln(n);
  writeln(timetostr(time));
  t:= 1 ;
  s:= 0 ;
  for i := 1 to n do
  begin
     s := s + t;
     t:= t*2;
  end;
  writeln(s);
  writeln(timetostr(time));
  read(s);

end.
