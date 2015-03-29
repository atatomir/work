const c= 99999999999999999;
var t,ti,p,r:Longint;
    a:array[1..4]of shortint;
    n:int64;

procedure next(ra:longint;act:int64);
var i:shortint;
begin
  if (act mod p = r)and(act < n) then n := act;

  if act <> 0 then dec(ra);
  for i := 1 to 4 do
  begin
    if ra <> 0 then next(ra,act*10+a[i]);
  end;
end;

begin
  assign(input,'cifre4.in'); reset(input);
  assign(output,'cifre4.out'); rewrite(output);

  readln(t);
  a[1] := 2; a[2] := 3; a[3] := 5; a[4] := 7;

  for ti := 1 to t do
  begin
    n := c;
    readln(r,p);

    next(11,0);     /// 1st param este nr de cifre care se cauta

    if n <> c then writeln(n) else writeln('-1');
  end;

  close(input);
  close(output);
end.
