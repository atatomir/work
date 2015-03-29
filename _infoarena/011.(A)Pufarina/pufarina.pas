var t,ti:longint;
    n,i,x,cmm:longint;
    nr:real;
    bufin,bufout:array[1..65000]of byte;
 
function cmmdc(a,b:longint):longint;
var t:longint;
begin
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
  assign(input,'pufarina.in'); reset(input);
  assign(output,'pufarina.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);
 
  readln(t);
  for ti := 1 to t do
  begin
    readln(n); cmm := 100000;
    for i := 1 to n do
    begin
      read(nr); nr := nr*1000;
      x := trunc(nr);
 
      cmm := cmmdc(cmm,x);
    end; readln();
 
    x := 100000 div cmm;
    if x > 50000 then
      writeln('ALEGERI FRAUDATE')
    else
      writeln(x);
  end;
 
 
 
  close(input);
  close(output);
end.