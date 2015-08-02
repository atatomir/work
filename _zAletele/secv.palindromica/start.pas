var maxg,posg: byte;
    a:string;
    i:byte;

procedure calc(a:string;i:byte);
var j,max,pos:byte;
begin

max := 1 ;

for j := 1 to i-1 do
begin
   if a[i-j] = a[i+j] then
   begin
   max:= max+2;
   pos := i-j;
   end
   else
   break;
end;
   if maxg < max then
   begin
   maxg:= max;
   posg:= pos;
   end;
end;

begin

writeln(' Scrie fraza cu litere mici si fara spatii ');
readln(a);

for i := 2 to length(a)-1 do
calc(a,i);


writeln('Cea mai  lunga secventa palendromica are ',maxg,' caractere ');
writeln('Primul caracter se afla pe pozitia ',posg);
write(' Cuvantul este : ');

for i := 1 to maxg  do
write(a[i+posg -1] );

writeln();
readln(maxg);








end.
