var n,inv:integer;



begin
inv := 0 ;
write('Scrie numarul');
readln(n);
if n=0 then
write(' Numarul invers este 0 ')
else
begin
repeat
inv := inv*10 + n mod 10;
n := n div 10;
until n =0;

writeln(inv);

read(n);
end;












end.