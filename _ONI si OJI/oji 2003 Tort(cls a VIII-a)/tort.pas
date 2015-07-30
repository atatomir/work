var n,m,cmm:longint;

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

begin
  assign(input,'tort.in'); reset(input);
  assign(output,'tort.out'); rewrite(output);

  readln(n,m);
  cmm := cmmdc(n,m);

  writeln((n div cmm)*(m div cmm),' ',cmm);

  close(input);
  close(output);
end.