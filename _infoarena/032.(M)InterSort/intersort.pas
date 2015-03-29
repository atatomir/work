var n,i,apar,incep:longint;
    a:array[1..100001]of longint;
    ap:array[1..100001]of boolean;
    bufin:array[1..65000]of byte;
    s:int64;

procedure formeaza(x:longint);
begin
  if a[x] <> incep then
  begin
    inc(apar);
    ap[x] := true;
    formeaza(a[x]);
  end;
end;


begin
  assign(input,'intersort.in'); reset(input);
  assign(output,'intersort.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); s := 0;

  for i := 1 to n do
  begin
    read(a[i]);
    ap[i] := false;
  end;

  if a[1]=1 then s := s + 2;
  for i := 1 to n do
  begin
    if ap[i] = false then
    begin
      if a[i] = i then continue;
      ap[i] := false;
      incep := a[i];
      apar := 1;
      formeaza(a[i]);
      s := s + apar+1;
    end;
  end;

  writeln(s-2);

  close(input);
  close(output);
end.
