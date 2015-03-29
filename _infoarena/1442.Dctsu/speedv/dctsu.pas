uses sysutils;
const n=276997;
var r,i,q:longint;
    a:array[0..n+1]of int64;
    bufin:array[1..65000]of byte;
    x:int64;
    s:string;

procedure QSort(lo,hi:longint);
var i,j:longint;
    t,m:int64;
begin
  i := lo; j := hi; m := (i+j)div 2;
  repeat
    while a[i] < a[m] do inc(i);
    while a[j] > a[m] do dec(j);
    if i <= j then
    begin
      t := a[i]; a[i] := a[j]; a[j] := t;
      inc(i); dec(j);
    end;
  until i > j;
  if j > lo then QSort(lo,j);
  if i < hi then QSort(i,hi);
end;

function CBinar(x:int64):boolean;
var i,j:longint;
    m:int64;
begin
  CBinar := false;
  i := 1; j := n;
  repeat
    m := (i+j)div 2;
    if x=a[m] then
    begin
      CBinar := true;
      break;
    end
    else
      if x < a[m] then j := m-1 else i := m+1;
  until i>j;
end;

begin
  assign(input,'dtcsu.in'); reset(input);
  assign(output,'dtcsu.out'); rewrite(output);
  settextbuf(input,bufin);

  for i := 1 to n do readln(a[i]);
  r := 0;

  QSort(1,3);

  readln(q);

  for i := 1 to q do
  begin
    readln(s); x := strtoint(s);
    if CBinar(x) then inc(r);
  end;

  write(r);

  close(input);
  close(output);
end.
