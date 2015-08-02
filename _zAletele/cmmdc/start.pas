var x,y:longint;

begin

writeln('Scrie primul numar , apoi al doilea');
readln(x,y);


if x<>y then

begin

repeat

if x<y then
y := y -x
else
x := x - y;





until x=y;

write('CMMDC=');
write(x);




end

else
begin
write('CMMDC='); write(x);
end;

read(x);






end.
