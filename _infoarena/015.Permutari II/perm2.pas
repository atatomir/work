var n,i,cont,x:longint;
    a:array[1..100001]of longint;
    b:array[1..50001]of longint;

function cmmdc(a,b:longint):longint;
var t:longint;
begin
  if a < b then
  begin
    t := a;
    a := b;
    b := t;
  end;

  while b <> 0 do
  begin
    a := a mod b;

    t := a;
    a := b;
    b := t;
  end;

  cmmdc := a;
end;

procedure trimite(target,pos:longint);
var x:longint;
begin
  if a[target] = 0 then
  begin
    inc(cont);
    b[cont] := pos;
  end
  else
  begin
    x := a[target];
    a[target] := 0;
    trimite(x,pos+1);
  end;
end;

begin
  assign(input,'perm2.in'); reset(input);
  assign(output,'perm2.out'); rewrite(output);

  readln(n);
  for i := 1 to n do read(a[i]);

  cont := 0;    b[1] := 1;

  for i := 1 to n do
  begin
    if (a[i] <> 0) and (a[i] <> i) then
    begin
      x := a[i] ;
      a[i] := 0;
      trimite(x,1);
    end;
  end;

  x := b[1];
  for i := 2 to cont do
    x := (x*b[i]) div cmmdc(x,b[i]);

  write(x);

  close(input);
  close(output);
end.
