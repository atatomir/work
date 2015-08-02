var n,i:longint;
    ant,a,b:char;
    s:string;
    aa,nn,an,na:array[-5..100005]of longint;

function getA:longint;
var x,y:longint;
begin
  x := aa[aa[-1]];
  y := an[an[-1]];

  if (x < y)and(aa[-1]<=aa[0]) then
  begin
    getA := x;
    inc(aa[-1]);
    ant := 'A';
  end
  else
  begin
    getA := y;
    inc(an[-1]);
    ant := 'N';
  end;
end;

function getN:longint;
var x,y:longint;
begin
  x := na[na[-1]];
  y := nn[nn[-1]];

  if (x < y)and(na[-1]<=na[0]) then
  begin
    getN := x;
    inc(na[-1]);
    ant := 'A';
  end
  else
  begin
    getN := y;
    inc(nn[-1]);
    ant := 'N';
  end;
end;

begin
  assign(input,'pitici5.in'); reset(input);
  assign(output,'pitici5.out'); rewrite(output);

  read(n); read(ant);
  readln(ant);

  aa[-1] := 1; nn[-1] := 1;
  an[-1] := 1; na[-1] := 1;
  aa[0] := 0; nn[0] := 0;
  an[0] := 0; na[0] := 0;

  for i := 1 to n do
  begin
    read(a); read(b); readln(b);
    s := a+b;

    if s = 'NN'then begin inc(nn[0]); nn[nn[0]]:= i; end;
    if s = 'AA'then begin inc(aa[0]); aa[aa[0]]:= i; end;
    if s = 'NA'then begin inc(na[0]); na[na[0]]:= i; end;
    if s = 'AN'then begin inc(an[0]); an[an[0]]:= i; end;
  end;

  while n > 0 do
  begin
    if ant = 'A' then
    begin
      write(getA,' ');
    end
    else
    begin
      write(getN,' ');
    end;

    dec(n);
  end;


  close(input);
  close(output);
end.
