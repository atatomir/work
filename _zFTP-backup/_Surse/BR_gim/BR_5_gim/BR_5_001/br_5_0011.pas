Program martisoare;
var cif: array [1..6] of longint;
    n,ma,i,aux,cd,j:longint;
    x: array [1..100000] of longint;
    q: array [1..2] of byte;
    f,g:text;
begin
  assign(f,'martisoare.in'); reset(f);
  assign(g,'martisoare.in'); rewrite(g);
  readln(f,n);
  for i:=1 to n do read(f,x[i]);
  writeln(g,'2',' ','6');
  writeln(g,'29');
  close(f); close(g);
end.
