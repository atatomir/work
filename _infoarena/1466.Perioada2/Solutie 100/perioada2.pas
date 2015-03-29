var n,i,q:longint;
    s:array[0..10000005]of char;
    pr:array[0..10000005]of longint;
    bufin:array[1..65000]of byte;

function nr_div(x:longint):int64;
var i,h:longint;
    p:int64;
begin
  nr_div := 1;
  h := trunc(sqrt(x))+1;
  for i := 2 to h do
  begin
    p := 0;
    while x mod i = 0 do
    begin
      inc(p);
      x := x div i;
    end;
    inc(p);
    nr_div := nr_div * p;
  end;
  if x <> 1 then nr_div := nr_div * 2;
end;

begin
  assign(input,'perioada2.in'); reset(input);
  assign(output,'perioada2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do read(s[i]);

  pr[1] := 0; q := 0;

  for i := 2 to n do
  begin
    while (q>0)and(s[q+1]<>s[i]) do q := pr[q];
    if s[q+1] = s[i] then inc(q);
    pr[i] := q;
  end;

  writeln(nr_div(n div (n-pr[n]))-1);

  close(input);
  close(output);
end.
