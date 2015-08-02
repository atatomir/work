program cladiri;
var f,g:text;
    x,a,n,i,y,j,c,z:longint;
    t,max:byte;
begin
  assign(f,'cladiri.in'); reset(f);
  assign(g,'cladiri.out'); rewrite(g);
  readln(f,n);
  for i:=1 to n do
    begin
      readln(f,x);
      a:=x;
      for j:=1 to n do
        begin
          t:=a mod 10;
          if t<>0 then
                   begin
                     z:=z+1;
                     a:=a div 10;
                   end;
          if t>max then
                     begin
                       max:=t;
                       y:=1;
                       c:=i;
                       end;
        if (t=max) and(i<>c) then
                              begin
                                y:=y+1;
                                c:=i;
                              end;

   end;
   write(g,max,' ',y);
   close(f); close(g);
end.
