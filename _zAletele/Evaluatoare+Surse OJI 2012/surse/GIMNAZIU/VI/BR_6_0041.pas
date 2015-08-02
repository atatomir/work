program cladiri;
var f,g:text;
    a:array[1..1000] of longint;
    i,x,r,n,max,j,t,s,inv:longint;
begin
  assign(f,'cladiri.out');reset(f);
  assign(g,'cladiri.in');rewrite(g);
  readln(f,n);
  for i:=1 to n do
   begin
     readln(f,a[i]);
     while a[i]<>0 do
       begin
         r:=a[i] mod 10;
         if max<r then
          begin
             max:=r;
             x:=x+1;
           end;
           inv:=inv*10+r;
        end;
        if a[i]=inv then t:=t+1;
  end;
  write(g,max,' ',x);
  write(g,t);
  close(f);
  close(g);
end.
