var p,po:string;
    i,n:integer;

begin

writeln('Scrie fraza pentru decodare:');
readln(p);
n:= length(p);
po:='';
i:= 1;


while i <= n do
begin
writeln(i);
writeln(n);

  if pos(p[i],'aeiouAEIOU') > 0 then
  begin

   if ((p[i+1] = 'p') or (p[i+1] ='P')) and (p[i+2] = p[i]) then
   po:= po + p[i]
   else
   begin
   write('Fraza este gresita');
   exit;
   end;
   i:= i + 3
  end

  else
  begin
  po:=po+ p[i];
  inc(i);
  end;




end;




write(po);
read(po);



end.
