const v:array[0..13] of longint= (0,1, 6, 31, 156, 781, 3906, 19531, 97656, 488281, 2441406, 12207031, 61035156, 1000000001);
const r:array[0..13] of longint= (1,5,25,125,625,3125,15625,78125,390625,1953125,9765625,48828125,244140625,1220703125);
var p,x,pr:longint;
    n:int64;

function cb(x:longint):longint;
var i,j,m:longint;
begin
  i := 0 ; j := 13;
  repeat
    m := (i+j)div 2 ;
    if x <= v[m] then
      j := m-1
    else
      i := m+1;
  until i > j;

  if v[i] <> p then dec(i);

  cb := i;
end;

function verif:boolean;
var pp,nr:longint;
begin
  pp := 0;  nr := n;
  while nr >=5 do
  begin
    nr := nr div 5;
    pp := pp + nr;
  end;

  verif := (pp = pr);
end;

begin
  assign(input,'fact.in'); reset(input);
  assign(output,'fact.out'); rewrite(output);

  readln(p); n := 0;  pr := p;
  if p = 0 then
  begin
    writeln(1);
    exit;
  end;

  while p >= 1 do
  begin
    x := cb(p);
    n := n + r[x];
    p := p - v[x];
  end;

  if verif then
    writeln(n)
  else
    writeln(-1);

  close(input);
  close(output);
end.
