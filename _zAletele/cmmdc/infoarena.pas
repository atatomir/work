var x,y:int64;
    f,fo:text;

begin


assign(f,'cmmdc.in');reset(f);
readln(f,x,y);
close(f);

if x<0 then x := -x;
if y<0 then y := -y;
if x <> y then
repeat
  if x<y then
  y := y -x
  else
  x := x - y;
until x=y ;

if x =1 then x:=0;


assign(fo,'cmmdc.out');
rewrite(fo);
writeln(fo,x);
close(fo);


end.
