{program livada 2010 cls a IX-a}

var m,i,majoritare,contor:byte;
    n,j,nr,ultima:longint;
    dco,tm,maxdco:longint;
    f:text;
    a:array[1..700000]of longint;

procedure afla_max_consecutive;
begin
  if nr= tm then inc(dco) else
  begin
  if dco > maxdco then maxdco := dco;
  dco := 1 ; tm := nr ;
  end;
end;

procedure afla_majoritar;
begin
  if contor = 0 then
  begin
    contor := 1 ;
    ultima := nr ;
  end
  else
  begin
    if ultima  = nr then
      inc(contor)
    else
      dec(contor);
  end;
end;

procedure afla_daca_e_mai_mare_de_jumatate;
begin
  if contor > 0 then
  begin
    contor := 0;
    for j := 1 to n do
      if a[j] = ultima then inc(contor);
    if contor > (n div 2) then  inc(majoritare);
  end;
end;

procedure scriere;
var fo:text;
begin
  assign(fo,'livada.out');
  rewrite(fo);
  writeln(fo,majoritare);
  writeln(fo,maxdco);
  close(f);
  close(fo);
end;

begin
  assign(f,'livada.in'); reset(f);
  readln(f,m,n);
  maxdco := 0;
  majoritare := 0;
  for i := 1 to m do
  begin
    dco:= 0;
    tm:= 0;
    contor := 0 ;
    ultima := -1;
    for j := 1 to n do
    begin
      read(f,nr);
      a[j] := nr;
      afla_max_consecutive;
      afla_majoritar;
    end;
    afla_daca_e_mai_mare_de_jumatate;
    readln(f);
  end;
  scriere;
end.
