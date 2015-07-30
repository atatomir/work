var n,i,c,r,x:longint;

begin
  readln(n);
  readln(x); c := x ; r := 1;
  for i := 2 to n do
  begin
    readln(x);
    if r = 0 then
    begin
      r := 1;
      c := x;
    end
    else
    begin
      if x = c then
        inc(r)
      else
        dec(r);
    end;
  end;
  writeln(c);

end.