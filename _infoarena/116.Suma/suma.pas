program suma_infoarena;

var n,suma,p:int64;
    f,fo:text;

begin
  assign(f,'suma.in'); reset(f);
  read(f,n,p); close(f);
  assign(fo,'suma.out'); rewrite(fo);
  suma := 0;
  if n mod 3 = 0 then
  begin
    suma := (n div 3 )mod p;
    suma := (suma * ((n-1) mod p)) mod p;
    suma := (suma * ((n+1) mod p)) mod p;
  end;
  if n mod 3 = 1 then
  begin
    suma := ((n-1) div 3 )mod p;
    suma := (suma * ((n) mod p)) mod p;
    suma := (suma * ((n+1) mod p)) mod p;
  end;
  if n mod 3 = 2 then
  begin
    suma := ((n+1)div 3 )mod p;
    suma := (suma * ((n) mod p)) mod p;
    suma := (suma * ((n-1) mod p)) mod p;
  end;
  write(fo,suma);
  close(fo);


end.
