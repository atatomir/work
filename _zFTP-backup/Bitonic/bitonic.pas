var t,ti,n,i,s1,s2,j:longint;
    a:array[1..1000]of longint;
    r:array[1..4,1..1000]of longint;
    v1,v2:array[1..1000]of longint;
    pasdoi:boolean;
    max:longint;

function cb(x:longint):longint;
var i,j,m:longint;
begin
  if s1 = 0 then
    cb := 1
  else
  begin
    i := 1; j := s1;
    repeat
      m := (i+j)div 2;
      if x <= v1[m] then
      begin
        j := m-1;
      end
      else
      begin
        i := m+1;
      end;
    until i > j;
    cb :=  i;
  end;
end;

function cbm(x:longint):longint;
var i,j,m:longint;
begin
  if s2 = 0 then
    cbm := 1
  else
  begin
    i := 1; j := s2;
    repeat
      m := (i+j)div 2;
      if x >= v2[m] then
      begin
        j := m-1;
      end
      else
      begin
        i := m+1;
      end;
    until i > j;
    cbm :=  i;
  end;
end;

procedure addmare(i:longint);
var t,x,h:longint;
begin
  x := a[i];
  t := cb(x); if t > s1 then inc(s1);
  v1[t] := x;
  h := 1; if pasdoi then h := 3;
  r[h,i] := t;
end;

procedure addmic(i:longint);
var t,x,h:longint;

begin
  x := a[i];
  t := cbm(x); if t > s2 then inc(s2);
  v2[t] := x;
  h := 2; if pasdoi then h := 4;
  r[h,i] := t;
end;

begin
  assign(input,'bitonic.in'); reset(input);
  assign(output,'bitonic.out'); rewrite(output);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    for i := 1 to n do read(a[i]); readln();

    s1 := 0; s2 := 0;   pasdoi := false;
    for i := 1 to n do
    begin
      addmare(i);
      addmic(i);
    end;

    pasdoi := true; s1 := 0; s2 := 0;
    for i := n downto 1 do
    begin
      addmare(i);
      addmic(i);
    end;

    max := -1;

    for i := 1 to n do
    begin
      if r[1,i] + r[3,i] - 1 > max then max := r[1,i] + r[3,i] - 1;
      if r[2,i] + r[4,i] - 1 > max then max := r[2,i] + r[4,i] - 1;
    end;

    writeln(max);

  end;



  close(input);
  close(output);
end.
