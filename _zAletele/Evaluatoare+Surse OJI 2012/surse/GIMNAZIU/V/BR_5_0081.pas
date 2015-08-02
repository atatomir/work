program bete;
var temp,i,n,l,k,p:integer;
    f,g:text;
    a,b:array [1..100] of  integer;
    nrmax,max1,max2:integer;
    inversari:boolean;
begin
  assign(f,'bete.in'); reset(f);
  assign(g,'bete.out'); rewrite(g);
  readln(f,n);
  for i:=1 to n do read(f,a[i]);
  readln(f);
  for i:=1 to n do read(f,b[i]);
  repeat
    inversari:=false;
    for i:=1 to n-1 do begin
                         if a[i]>a[i+1] then begin
                                               temp:=a[i];
                                               a[i]:=a[i+1];
                                               a[i+1]:=temp;
                                               inversari:=true;
                                             end;
                       end;
  until (not inversari);
  repeat
    inversari:=false;
    for i:=1 to n-1 do begin
                         if b[i]<b[i+1] then begin
                                               temp:=b[i];
                                               b[i]:=b[i+1];
                                               b[i+1]:=temp;
                                               inversari:=true;
                                             end;
                       end;
  until (not inversari);
  l:=a[1]+b[1];
  max1:=0; max2:=0;
  for i:=1 to n do begin
                     if max1<a[i] then max1:=a[i];
                     if max2<b[i] then max2:=b[i];
                   end;
  nrmax:=1; k:=max1+max2;
  writeln(g,l);
  writeln(g,k);
  if l=k then nrmax:=n;
  writeln(g,nrmax);
  close(f);
  close(g);
end.