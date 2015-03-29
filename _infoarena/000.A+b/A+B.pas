var a,b,s:longint;
    f:text;
begin
  assign(f,'adunare.in'); reset(f);
  readln(f,a);
  readln(f,b);
  close(f);
  assign(f,'adunare.out'); rewrite(f);
  s:= a+b;
  write(f,s);
  close(f);
end.
