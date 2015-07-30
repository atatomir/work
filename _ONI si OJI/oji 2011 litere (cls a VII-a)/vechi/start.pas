type litera=record
     cod:byte;
     char:char;
     end;

var f,fo,help:text;
    n,i:longint;
    s:string;
    a:array[1..26]of litera;
    b,j,lit,grupuri:byte;
    gasit:boolean;
    suma:longint;
    nr,mult:int64;

begin
assign(f,'litere.in'); reset(f);
assign(fo,'litere.out'); rewrite(fo);

grupuri:= 0;
lit:= 1;

readln(f,n);
readln(f,s);
readln(f,b);


for i := 1 to length(s)-1 do
begin
gasit:= false;

 for j := 1 to b do
 begin

   if s[i]= a[j].char then
   begin
   gasit:= true;
   break;
   end;

 end;

if gasit = false then
begin
read(f,a[lit].cod);
a[lit].char := s[i];
inc(lit);
end;


end;


for n := 1 to length(s)-1 do
begin

   if ((  pos(s[i] , 'AEIOU') > 0 ) and (pos(s[i+1] , 'AEIOU') = 0 )) or ((  pos(s[i+1] , 'AEIOU') > 0 ) and (pos(s[i] , 'AEIOU') = 0 )) then
   begin
   inc(grupuri);
   end;

end;


writeln(fo,'Numarul de grupuri este : ',grupuri);

assign(help,'help.bin');
rewrite(help);


for n := 1 to length(s) do
begin

  for i := 1 to 26 do
  begin

    if a[i].char = s[n] then
    begin
    write(fo,a[i].cod);
    write(help,a[i].cod);
    break;
    end;

  end;

end;

writeln(help,' ');
close(help); reset(help);

writeln(fo,' ');

suma:= 0 ;
read(help,nr);
close(help);
reset(help);
read(help,s);
close(help);
mult:= 1;

for n := 1 to length(s) do
begin

suma:= suma+ (nr mod mult);
mult := mult*10;

end;


writeln(fo,'Suma este : ',suma);


close(f);
close(fo);
end.
