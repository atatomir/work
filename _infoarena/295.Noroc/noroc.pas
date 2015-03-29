program noroc;
var x,m:longint;
    i:int64;


begin
  assign(input,'noroc.in'); reset(input);
  assign(output,'noroc.out'); rewrite(output);

  readln(x,m);

  if x >= m then
    write('1.0000000')
  else
  begin
    i := (100000000 div m)* x ;
    if i mod 10 >= 5 then i := i + 10;
    i := i div 10;
    write('0.');
    write(10000000-i);
  end;

  close(input);
  close(output);
end.
