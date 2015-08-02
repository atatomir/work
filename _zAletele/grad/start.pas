var grad:string;
    x,play,ramas,rh,rm:longword;
begin
x:= 0;
writeln('La ce grad va ajunge?');
readln(grad);
if grad ='member' then
x := 1440 ;
if grad ='popular' then
x := 3600 ;
if grad ='expert' then
x := 7200  ;
if grad ='veteran' then
x := 48000 ;
if grad ='legend' then
x := 60000 ;
writeln('Cate minute jucate are ?');
readln(play);
ramas := x-play ;
rh := ramas div 60 ;
rm := ramas mod 60 ;
write('Au mai ramas ');
write(ramas);
writeln('minute');
write('Au mai ramas');
write(rh);
write(' ore ');
write('si');
write(rm);
writeln('minute');
writeln('Scrie exit si apoi ENTER pentru a iesi ');
read(grad);
















end.
