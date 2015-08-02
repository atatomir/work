program galbeni;
var f,g:text;
    s,k,j,t:byte;
    n,i,z,x:longint;

begin
  assign(f,'galbeni.in'); reset(f);
  assign(g,'galbeni.out'); rewrite(g);
  read(f,s,k,n);
  for i:=1 to n do
    begin
      if i>1 then
              begin
                s:=x;
                x:=0;
              end;
      if i=n then z:=s;
      for j:=1 to k do
        begin
          t:=s mod 10;
          if t<>0 then
                    begin
                      if j=1 then x:=s*t;
                      if j>1 then x:=x*t;
                    end;
          s:=s div 10;
          t:=0;
        end;
      x:=x*8 div 9 mod 100;
    end;
  writeln(g,z);
  close(f);
  close(g);
end.
