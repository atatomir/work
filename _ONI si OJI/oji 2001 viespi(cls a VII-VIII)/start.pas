procedure rezolva_problema ;
var n,p,q,i:byte;
    f,fo:text;

begin
  assign(f,'viespi.in');reset(f);
  readln(f,n);read(f,p,q); close(f);

  for i := 3 to n do
  begin
  q:= (q*4)-p;
  p := (q + p) div 4;
  end;
  assign(fo,'viespi.out'); rewrite(fo);
  write(fo,q);
  close(fo);
end;

begin
rezolva_problema;
end.