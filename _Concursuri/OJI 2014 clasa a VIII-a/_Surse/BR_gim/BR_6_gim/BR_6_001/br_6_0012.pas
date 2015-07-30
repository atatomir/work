program munte;
var m:boolean;
    a,b:array[1..100] of longint;
    n,i,k,j,l,nr:byte;
    f,g:text;
begin
  assign(f,'munte.in'); reset(f);
  assign(g,'munte.out'); rewrite(g);
  readln(f,n);
  for i:=1 to n do read(f,a[i]);
  m:=true;
  j:=0;
  nr:=0;
  while m do
    begin
      inc(j);
      k:=0;
      m:=false;
      for i:=2 to n-1 do
        if (a[i-1]<a[i]) and (a[i]>a[i+1])
          then begin
                 m:=true;
                 inc(k);
                 inc(nr);
                 b[k]:=i;
               end;
      if j=1 then writeln(g,k);
      for i:=1 to k do
        begin
          for l:=b[i] to n-1 do a[l]:=a[l+1];
          dec(n);
          for l:=i+1 to k do dec(b[l]);
        end;
    end;
  writeln(g,nr);
  writeln(g,n);
  close(f);
  close(g);
end.