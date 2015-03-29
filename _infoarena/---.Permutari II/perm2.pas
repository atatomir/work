var n,i,lung:longint;
    a:array[0..100005]of longint;
    k,t:longint;
    bufin:array[1..65000]of byte;

function get_lung(pos:longint):longint;
var go:longint;
begin
  get_lung := 0;
  while a[pos] <> -1 do
  begin
    inc(get_lung);
    go := a[pos];
    a[pos] := -1;
    pos := go;
  end;
end;

procedure inverse(var a,b:longint);inline;
begin
  t := a; a := b; b := t;
end;

function cmmdc(a,b:longint):longint;
begin
  if a > b then inverse(a,b);

  while b > 0 do
  begin
    a := a mod b;
    inverse(a,b);
  end;

  cmmdc := a;
end;

function cmmmc(a,b:longint):longint;
begin
  cmmmc := a*b div cmmdc(a,b);
end;

begin
  assign(input,'perm2.in'); reset(input);
  assign(output,'perm2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do read(a[i]);
  k := 1;

  for i := 1 to n do
  begin
    if a[i] <> -1 then
    begin
      lung := get_lung(i);
      k := cmmmc(k,lung);
    end;
  end;

  writeln(k);

  close(input);
  close(output);
end.