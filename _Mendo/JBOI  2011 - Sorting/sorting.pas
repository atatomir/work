var n,i,x,min:longint;
    cmm:longint;
    v:array[0..100000]of longint;

function cmmdc(a,b:longint):longint;
var t:longint;
begin
  if a = 1 then begin cmmdc := b; exit; end;

  if a < b then
  begin
    t := a; a := b ; b := t;
  end;

  while b <> 0 do
  begin
    a := a mod b;
    t := a; a := b ; b := t;
  end;
  cmmdc := a;
end;

begin
  readln(n);  cmm := 1;
  for i := 1 to n do
  begin
    read(x);
    if x < i then cmm := cmmdc(cmm,i-x);
  end;

  v[0] := 0;
  for i := 1 to cmm do
    if cmm mod i = 0 then
    begin
      inc(v[0]);
      v[v[0]] := i;
    end;

  writeln(v[0]);
  for i := 1 to v[0] do write(v[i],' ');
end.