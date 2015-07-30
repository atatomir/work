uses sysutils;

var f,fo:text;
    x,y:byte;
    i:int64;
//    t1,t2:double;



procedure cauta(a,b:byte);
begin
   if a+1 <=x then
     cauta(a+1,b);
   if b+1 <= y then
     cauta(a,b+1);
   if (a=x) and (b=y) then
     inc(i);
end;


begin
  //t1:= time;
  //writeln(timetostr(time));
  assign(f,'paianjen.in'); reset(f);
  read(f,x,y); close(f);
  i := 0;
  cauta(0,0);
  assign(fo,'paianjen.out'); rewrite(fo);
  write(fo,i);
  close(fo);
  //writeln(timetostr(time));
  //t2:= time;
  //writeln(round((t2-t1)*24*3600*1000000));

end.
