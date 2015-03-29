var n,m,i,j:longint;
    a:array[1..16,1..16]of longint;
    c:array[1..16]of shortint;
    bufin:array[1..65000]of byte;
    s:int64;

procedure calc;
var st,sl:longint;
begin
  st := 0;
  for i := 1 to n do
  begin
    sl := 0;
    for j := 1 to m do
      sl := sl + a[i,j]*c[j];
    if sl < 0 then st := st - sl else st := st + sl;
  end;
  if st > s then s := st;

end;

procedure back(pas:longint);
begin
  if pas = m then
  begin
    c[pas] := 1;
    calc;
    c[pas] := -1;
    calc;
  end
  else
  begin
    c[pas] := 1;
    back(pas+1);
    c[pas] := -1;
    back(pas+1);
  end;
end;

begin
  assign(input,'flip.in'); reset(input);
  assign(output,'flip.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);
  for i := 1 to n do
  begin
    for j := 1 to m do
      read(a[i,j]);
    readln();
  end;

  s := 0;
  back(1);

  writeln(s);


  close(input);
  close(output);
end.