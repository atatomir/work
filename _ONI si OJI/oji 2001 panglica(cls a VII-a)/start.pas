uses sysutils;

type max=record
     fr,tinc,tsfr:word;
     cul:byte;
end;

var n,i,j:word;
    c:byte;
    a:array[1..10000]of byte;
    maxim:max;
    f,fo:text;
//    t1,t2:double;


begin
//t1:= time;
//writeln(timetostr(time));
assign(f,'panglica.in'); reset(f);
assign(fo,'panglica.out'); rewrite(fo);

readln(f,n,c);

for i := 1 to n do
begin
  readln(f,a[i]);
  //writeln(a[i]);
end;
close(f);

for i := 1 to (n-1) div 2 do
begin
  for j := 1 to n-i-1 do
  begin
    if a[i]=a[n-j+1] then
    begin
      //writeln(a[i],' ',a[n-j+1],' ',i,'-',n-j+1);
      if n-(i+j-2) > maxim.fr then
      begin
         maxim.fr:= n-(i+j-2);
         maxim.tinc := i -1;
         maxim.tsfr := j-1;
         maxim.cul := a[i];
      end;
      break;
    end;
  end;
end;



writeln(fo,maxim.fr);
writeln(fo,maxim.cul);
writeln(fo,maxim.tinc);
writeln(fo,maxim.tsfr);




close(fo);
//writeln(timetostr(time));
//t2:= time;
//write(round((t2-t1)*24*3600*1000000));
end.
