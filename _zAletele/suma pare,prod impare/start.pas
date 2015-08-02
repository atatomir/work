var n,s,p,uc:integer;

begin
s := 0;
p:= 1;

write('Scrie numarul dorit');
readln(n);

if n = 0 then
write(' S= 0 si P = 1')
else
begin

repeat
uc := n mod 10;
n:= n div 10;
if uc mod 2 = 0 then
s := s + uc;
if uc mod 2 = 1 then
p := p * uc;


until n=0;

write('S='); writeln(s);
write('P='); writeln(p);
read(p);



end;










end.