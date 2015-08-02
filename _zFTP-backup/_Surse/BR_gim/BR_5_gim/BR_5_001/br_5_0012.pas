Program piramide;
var n,i,j,x,k,aux,d,px,aux1,c,b,v,r,eg,egmax,pir:longint;
    pr: array [0..100000] of longint;
    op: array [0..100000] of longint;
    ca: array [1..100000] of longint;
    f,g:text;
begin
  assign(f,'piramide.in'); reset(f);
  assign(g,'piramide.out'); rewrite(g);
  readln(f,n,x,k);
  for i:=1 to k do read(f,ca[i]);
  pr[1]:=1;
  op[1]:=3;
  aux1:=n;
  b:=2;
  while aux1>0 do
   begin
     inc(d);
     aux1:=aux1-op[d]+op[d-1];
     for i:=pr[d] to op[d] do if i=x then px:=d;
     inc(b);
     pr[d+1]:=op[d]+1;
     op[d+1]:=(b*(b+1) div 2)+op[d];
     if op[d]>aux1 then begin
                          c:=aux1;
                          aux1:=0;
                        end;
   end;
  for i:=1 to d do
    begin
      for j:=pr[i] to op[i] do
        for v:=1 to k do begin
                           if j=ca[v] then begin
                                             inc(eg);
                                           end;
                           if ca[v]>j then break;
                         end;
      if eg>egmax then begin
                         egmax:=eg;
                         eg:=0;
                         pir:=i;
                       end;
      eg:=0;
    end;
  if eg>egmax then pir:=i;
  writeln(g,px);
  writeln(g,d);
  writeln(g,c);
  writeln(g,pir);
  close(f); close(g);
end.
