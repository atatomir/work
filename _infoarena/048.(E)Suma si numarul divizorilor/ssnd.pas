const def=1005000;
      modd=9973;
var t,ti:longint;
    i,p:longint;
    c:array[0..def+5]of boolean;
    prim:array[0..80000]of longint;
    nr,sum,d,n,h:int64;
    bufin,bufout:array[1..65000]of byte;

procedure ciur();
var i,hh,j,h:longint;
begin
  prim[0] := 0;
  for i := 2 to def do
    c[i] := true;
  h := trunc(sqrt(def));
  for i := 2 to h do
    if c[i] then
    begin
      hh := def div i;
      for j := i to hh do c[i*j] := false;
    end;
  for i := 1 to def do
    if c[i] then
    begin
      inc(prim[0]); prim[prim[0]] := i;
    end;
end;

function up(a,b:int64):int64;
var x:int64;
begin
  up := 1;
  while b <> 0 do
  begin
    if b mod 2 = 0 then
    begin
      a := a*a;
      b := b div 2;
    end
    else
    begin
      up := up * a;
      dec(b);
    end;
  end;
end;

begin
  assign(input,'ssnd.in'); reset(input);
  assign(output,'ssnd.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  ciur();

  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    nr := 1; sum := 1;
    h := trunc(sqrt(n));
    i := 0;
    while (prim[i+1] <= h)and(n<>1) do
    begin
      inc(i);
      p := 1; d := prim[i];

      while n mod prim[i] = 0 do
      begin
        inc(p);
        n := n div prim[i];
      end;

      if p > 1 then
      begin
        d := up(prim[i],p);
        nr := (nr * p)mod modd;
        sum := (sum * ((d-1) div (prim[i]-1)))mod modd;
        h := trunc(sqrt(n));
      end;
    end;
    if n <> 1 then
    begin
      nr := nr * 2; nr := nr mod modd;
      sum := sum * ((n*n-1) div (n-1)); sum := sum mod modd;
    end;

    writeln(nr,' ',sum);

  end;


  close(input);
  close(output);
end.
