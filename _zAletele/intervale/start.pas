program intervale_reunire;

type it=record
     x,y:integer;
     end;

var f:text;
    i,j,rx,ry,n:integer;
    a:array[1..100] of it;
    t:it;

begin
assign(f,'file.bin');reset(f);

readln(f,n);

for i := 1 to n do
readln(f,a[i].x,a[i].y);

for i := 1 to n-1 do
begin
 for j := i+1 to n do
 begin
   if a[i].x > a[j].x then
   begin
   t := a[i];
   a[i] := a[j] ;
   a[j] := t;
   end;
 end;
end;
rx:= a[1].x;
ry := a[1].y;

for i := 2 to n do
begin

  if a[i].x > ry then
  begin
  writeln(rx,' ',ry);
  rx := a[i].x;
  ry := a[i].y;
  end
  else
  if ry< a[i].y then
  ry := a[i].y;

end;



writeln(rx,' ',ry);

read(ry);
close(f);
end.
