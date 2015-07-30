var a,b:array[1..10]of longint;
    n,i,si,nn,nr,l,ssi,sum,max:longint;
    s:array[1..500]of byte;

function mmic(i,j:longint):boolean;
var maxcf,aa,bb,nra,nrb:longint;
begin
  mmic := true;
  maxcf := b[i]; if b[j] > maxcf then maxcf := b[j];
  aa := a[i]; bb := a[j]; nra := b[i]; nrb := b[j];

  while nra < maxcf do
  begin
    inc(nra);
    aa := aa*10;
  end;
  while nrb < maxcf do
  begin
    inc(nrb);
    bb := bb*10;
  end;
  if aa > bb then mmic := false;

end;

procedure sort;
var ok:boolean;
    i,t:longint;
begin
  ok := true;
  while ok do
  begin
    ok := false;
    for i := 1 to si-1 do
       if not mmic(i,i+1) then
       begin
         ok := true;
         t := a[i]; a[i] := a[i+1]; a[i+1] := t;
         t := b[i]; b[i] := b[i+1]; b[i+1] := t;
       end;
  end;
end;

function nrcf(n:longint):longint;
begin
  nrcf := 0;
  while n <> 0 do
  begin
    inc(nrcf);
    n := n div 10;
  end;
end;

begin
  assign(input,'templu.in'); reset(input);
  assign(output,'templu.out'); rewrite(output);

  readln(n,l); nn := l+2;

  nr := (n-1)*l; si := 0; sum := 0;

  for i := 1 to (l div 2) do
  begin
    nn := nn-2;
    nr := nr + nn; sum := sum + 2*nr;

    inc(si); a[si] := nr;
    inc(si); a[si] := nr;

    b[si] := nrcf(nr);
    b[si-1] := b[si];

  end;

  if l mod 2 = 1 then
  begin
    inc(si);
    a[si] := nr + nn-2;  sum := sum + nr + nn-2;
    b[si] := nrcf(nr);
  end;

  inc(si); a[si] := sum;  b[si] := nrcf(sum);

  Sort;

  ssi := 0;

  for i := si downto 1 do
  begin
    while a[i] <> 0 do
    begin
      inc(ssi); s[ssi] :=  a[i] mod 10;
      a[i] := a[i] div 10;
    end;
  end;

  for i := ssi downto 1 do write(s[i]); writeln();

  max := -1;
  for i := 1 to ssi-1 do
  begin
    sum := s[i+1]*10 + s[i];
    if sum > max then max := sum;
  end;

  writeln(max);



  close(input);
  close(output);
end.
