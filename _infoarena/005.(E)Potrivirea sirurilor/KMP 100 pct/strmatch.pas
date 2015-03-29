var n,m,i,j,q:longint;
    a,b:ansistring;
    bufin,bufout:array[1..65000]of byte;
    v:array[0..1005]of longint;
    pr:array[0..2000005]of longint;

procedure make_pref();inline;
var i,q:longint;
begin
  pr[1] := 0; q := 0;
  for i := 2 to n do
  begin
    while (q>0)and(a[q+1]<>a[i]) do q := pr[q];
    if a[q+1] = a[i] then inc(q);
    pr[i] := q;
  end;
end;

begin
  assign(input,'strmatch.in'); reset(input);
  assign(output,'strmatch.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(a); n := length(a); a := a + '!';
  readln(b); m := length(b);
  v[0] := 0;

  make_pref();

  q := 0;
  for i := 1 to m do
  begin
    while (q>0)and(a[q+1]<>b[i]) do q := pr[q];
    if a[q+1] = b[i] then inc(q);
    if q = n then
    begin
      inc(v[0]);
      if v[0] <= 1000 then v[v[0]] := i-q;
    end;
  end;

  writeln(v[0]);  if v[0] > 1000 then v[0] := 1000;
  for i := 1 to v[0] do write(v[i],' ');

  close(input);
  close(output);
end.