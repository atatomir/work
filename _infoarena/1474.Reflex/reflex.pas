var a,b,c,ture,parti,pos:int64;

function cmmdc(a,b:int64):int64;
var t:int64;
begin
  if a < b then
  begin
    t := a; a := b; b := t;
  end;

  while b <> 0 do
  begin
    a := a mod b;
    t := a; a := b; b := t;
  end;
  cmmdc := a;
end;

begin
  assign(input,'reflex.in'); reset(input);
  assign(output,'reflex.out'); rewrite(output);

  readln(a,b); dec(a); dec(b);
  c := (a*b) div cmmdc(a,b);

  ture := c div a;
  parti := c div b;

  if ture mod 2 = 0 then
  begin
    if parti mod 2 = 0 then
      pos := 1
    else
      pos := 2;
  end
  else
  begin
    if parti mod 2 = 0 then
      pos := 4
    else
      pos := 3;
  end;

  writeln(c+1,' ',pos);
  writeln(ture-1,' ',parti-1);

  close(input);
  close(output);
end.