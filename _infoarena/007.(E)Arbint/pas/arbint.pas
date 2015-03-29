var n,m,i,fr,v1,v2,t,st,dr,op,max,fin,last:longint;
    aint:array[0..600005]of longint;
    bufin,bufout:array[1..65000]of byte;

function p(x:longint):longint;
begin p := x div 2; end;

function c1(x:longint):longint;
begin c1 := 2*x; end;

function c2(x:longint):longint;
begin c2 := 2*x+1; end;

procedure verif(x:longint);
var v1,v2:longint;
begin
  v1 := aint[c1(x)];
  v2 := aint[c2(x)];
  if v2 > v1 then v1 := v2;
  if aint[x] <> v1 then
  begin
    aint[x] := v1;
    verif(p(x));
  end;
end;

procedure query(pos,i,j,il,jl:longint);
var i1,i2,j1,j2:longint;
begin
  if il=jl then
  begin
    if aint[pos] > max then max := aint[pos];
    exit;
  end;

  if (i <= il)and(jl <= j) then
  begin
    if max < aint[pos] then max := aint[pos];
  end
  else
  begin
    i1 := il; j1 := (il+jl)div 2;
    i2 := (il+jl)div 2+1 ; j2 := jl;

    if j1 >= i then query(c1(pos),i,j,i1,j1);
    if i2 <= j then query(c2(pos),i,j,i2,j2);
  end;
end;

begin
  assign(input,'arbint.in'); reset(input);
  assign(output,'arbint.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n,m);

  fr := 1; i := 1;
  while i*2<n do begin i := i*2; fr := fr + i; end;
  fin := fr + 2*i; last := i;

  for i := 1 to n do read(aint[fr+i]); readln();
  for i := fr+n+1 to fin do aint[i] := 0;

  for i := fr downto 1 do
  begin
    v1 := aint[c1(i)];
    v2 := aint[c2(i)];
    if v1 > v2 then aint[i] := v1 else aint[i] := v2;
  end;

  for t := 1 to m do
  begin
    readln(op,st,dr);
    case op of
      0:begin
          max := 0;
          query(1,st,dr,1,2*last);
          writeln(max);
        end;
      1:begin
          aint[fr+st] := dr;
          verif(p(fr+st));
        end;
      end;
  end;


  close(input);
  close(output);
end.