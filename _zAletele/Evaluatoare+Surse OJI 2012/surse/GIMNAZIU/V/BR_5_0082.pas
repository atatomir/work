program chibrituri;
var f,g:text;
    n,m:longint;
    hh,mm:byte;
    a,b:longint;
begin
  assign(f,'chibrituri.in'); reset(f);
  assign(g,'chibrituri.out'); rewrite(g);
  readln(f,n,m);
  close(f); close(g);
end.
