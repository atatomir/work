program galbeni;
var s,r,x,r1,k,n,y,t:longint;
    f,g:text;
begin
  assign(f,'galbeni.in'); reset(f);
  assign(g,'galbeni.out'); rewrite(g);
  readln(f,s,k,n);
  x:=s;
  for i:=1 to k do
    begin
  while s<>0 do
    begin
      r:=s mod 10;
      s:=s div 10;
    end;
      x:=x*r;
      x:=x*8;
      x:=x div 9;
    while x<>0 do
     begin
       r1:=x mod 10;
       t:=r1;
       x:=x div 10;
     end;
     y:=r1*10+;
     if y<10 then y:=y*10+9;
     writeln(g,y);
     close(f);
     close(g);
end.
