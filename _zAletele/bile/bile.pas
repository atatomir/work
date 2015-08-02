type obs=record
   x,y:word;
   end;

var n,m,p,i:word;
    a:array[1..2000]of word;
    b:array[1..10000]of obs;
    inv:boolean;
    t:obs;
    f:text;


begin

assign(f,'bile.in'); reset(f);

readln(f,n,m,p);

for i := 1 to p do
readln(f,b[i].x,b[i].y);

repeat
inv:=false;

  for i := 1 to p-1 do
    if b[i].x > b[i+1].x then
    begin
    t := b[i];
    b[i]:=b[i+1];
    b[i+1]:= t;
    inv:= true;
    break;
    end;

until inv = false;

for i:= 1 to m do
readln(f,a[i]);


for i := 1 to p do
begin
a[b[i].y +1]:= a[b[i].y +1] +( a[b[i].y] div 2);
a[b[i].y -1] :=a[b[i].y -1]+ ( (a[b[i].y]+1) div 2);
a[b[i].y]:= 0;

end;

for i := 1 to m do
writeln(a[i]);




close(f);
readln(i);
end.

