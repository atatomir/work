var x,t:int64;
    i,n:longint;
begin
  readln(n);
  for i := 1 to n do
  begin
    readln(x);
    t := trunc(sqrt(2*(x-1)));
    if x = t*(t+1)div 2 +1 then
      write('1 ') else write('0 ');
  end;

end.