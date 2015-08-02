var x,y:int64;
    i,dif1,dif2,cat,dt:integer;


begin
dt:= 1;
writeln('Scrie numarul dorit');
readln(x);
y := x;
cat := x;
repeat

dt := dt*2;
cat := cat div 2 ;


until cat=1;

dif1 := y - dt;
dif2 := dt * 2 - y;

if dif1 < dif2 then
begin
write('Cea mai apropiata putere a lui 2 este:');
write(dt);
end;

if dif1 > dif2 then
begin
write('Cea mai apropiata putere a lui 2 este:');
write(dt * 2);
end;

if dif1=dif2 then
begin
write('Cele mai apropiate puteri ale lui s sunt:' );
write(dt);
write(' ');
write(dt* 2);
end;














read(i);
end.
