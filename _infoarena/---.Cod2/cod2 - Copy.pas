const modd = 9901;
var n,k,p,i,op:longint;
    a:array[1..26]of longint;
    c:char;
    sum,l:int64;

function aranj(n1,k1:longint):int64;
var i1:longint;  v:int64;
begin
  if n1 < k1 then
  begin
    aranj := 0; exit;
  end
  else
  begin
    v := 1;
    for i1 := 1 to k1 do
      v := (v*(n1-i1+1))mod modd;
  end;
  aranj := v;
end;

begin
  assign(input,'cod1.in'); reset(input);
  assign(output,'cod1.out'); rewrite(output);

  readln(k);

  for i := 1 to 26 do a[i] := 0;

  while not eof(input) do
  begin
    read(c); op := ord(c)- $60;
    if (op <= 26)and(op>0) then
    begin
      inc(a[op]);
    end
    else
      continue;
  end;

  n := 0 ; p := 0;
  for i := 1 to 26 do
  begin
    if a[i] = 1 then
    begin
      inc(n);
    end
    else
    if a[i] > 1 then
    begin
      inc(n); inc(p);
    end;
  end;
    //writeln(n,' ',k,' ',p);
  case k of
    1: writeln(n mod modd);
    2: writeln((n*(n-1)+p)mod modd);
    else
    begin
      sum := aranj(n,k) mod modd;
      l := (p *(n-1)) mod modd;
      l := l div 2; l := (l *n) mod modd;
      l := (l*aranj(n-1,k-2))mod modd;
      sum := (sum + l)mod modd;

      writeln(sum);
    end;
  end;

  close(input);
  close(output);
end.
