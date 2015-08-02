uses sysutils;
var n,i:longword;
    x:longword;
    u1,u2,u3,u4,c1,c2,s:longword;
    f,fo:text;
    t1,t2:tdatetime;

begin
  t1:=now;

  assign(f,'3.in');reset(f);
  assign(fo,'3.out');rewrite(fo);
  c1:=0;c2:=0;s:=0;
  readln(f,n);
  for i:= 1 to n do
  begin
    read(f,x);
    s := s + (x mod 3);
    //writeln(x,' ',x mod 3,' ',s);
    if (c1 = 0)and(x mod 3 =1) then begin inc(c1); u1:=x; end
    else
    begin
      if (c1 = 1)and(x mod 3 =1) then begin inc(c1); u2:=x; end
      else
      begin
        if (c2 = 0)and(x mod 3 =2) then begin inc(c2); u3:=x; end
        else
        if (c2 = 1)and(x mod 3 =2) then begin inc(c2); u4:=x; end;
      end;
    end;
  end;

  s:= s mod 3;
  if s =0 then begin writeln(fo,n);writeln(fo,'Toate elementele sunt incluse in suma');end;
  if s =1 then
    if c1 > 0 then begin writeln(fo,n-1);writeln(fo,u1); end else begin writeln(fo,n-2); writeln(fo,u3,' ',u4);    end;
  if s = 2 then
    if c2 > 0 then begin writeln(fo,n-1); writeln(fo,u3); end else begin writeln(fo,n-2); writeln(fo,u1,' ',u2);   end;
  close(f);
  close(fo);

  t2:=now;
  //writeln(t2,' ',t1);
  writeln(round(24*3600*1000000*(t2-t1)));
end.
