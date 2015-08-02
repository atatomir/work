program castane;
var n:longint;

function suma_cifre (nr:longint):longint;
begin
suma_cifre := 0;
repeat
suma_cifre := suma_cifre + ( nr mod 10);
nr := nr div 10 ;
until nr= 0;
if suma_cifre > 9 then
suma_cifre(suma_cifre);
end;

begin
readln(n);
n := suma_cifre(n);

writeln(n);

readln(n);






end.
