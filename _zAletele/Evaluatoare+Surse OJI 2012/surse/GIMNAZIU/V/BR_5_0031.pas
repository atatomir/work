Program bete;
var n,i,maxa,maxb,bmax,minb,bi:longint;
    f,g:text;
    a:array [1..1000] of longint;
    b:array [1..1000] of longint;
    sp: CHAR;
begin
  assign(f,'bete.in'); reset(f);
  assign(g,'bete.out'); rewrite(g);
  readln(f,n);
  for i:=1 to n do read(f,a[i],sp);
  maxa:=a[i];
  readln(f);
  for i:=1 to n do
    read(f,b[i],sp);
  for i:=2 to n do if maxa<a[i] then maxa:=a[i];
  maxb:=b[i]; minb:=b[i];
  for i:=2 to n do begin
                     if minb>b[i] then minb:=b[i];
                     if maxb<b[i] then maxb:=b[i];
                   end;
  bi:=maxa+minb;
  writeln(g,bi);
  bmax:=maxa+maxb;
  writeln(g,bmax);
  close(f); close(g);
end.
