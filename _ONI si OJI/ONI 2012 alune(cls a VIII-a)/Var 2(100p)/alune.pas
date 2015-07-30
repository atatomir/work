const max = 2000000001;
var n,m,i,x,min:longint;
    mm:int64;
    bufin:array[1..65000]of byte;
    ok:boolean;

function cmmdc(a,b:int64):int64;
var t:int64;
begin
  while b <> 0 do
  begin
    a := a mod b;
    t := a ; a := b ; b := t;
  end;
  cmmdc := a;
end;

function cmmmc(a,b:int64):int64;
begin
  cmmmc := (a*b)div cmmdc(a,b);
end;

begin
  assign(input,'alune.in'); reset(input);
  assign(output,'alune.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);
  read(mm);   ok := true;   min := mm;

  for i := 2 to n do
  begin
    read(x);
    if x < min then min := x;
    if ok then
    begin
      mm := cmmmc(mm,x);
      if mm >= max then  ok := false;
    end;
  end;

  readln();
  for i := 1 to m do
  begin
    read(x);
    x := x mod mm;
    if x < min then
      write('1')
    else
      write('0');
  end;

  close(input);
  close(output);
end.
