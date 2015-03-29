var n,i:longint;
    a:array[1..100000] of longint;
    f,fo:text;
    msc:longint;
    t:array[1..3000000]of longint;
    gata:boolean;

begin
  assign(f,'mutari.in'); reset(f);
  readln(f,n);
  for i := 1 to n do read(f,a[i]);
  close(f);

  msc := 0;
  repeat
    gata := true;
    for i := n-1 downto 1 do
    begin
      if a[i+1]- a[i] > 0 then
      begin
        inc(msc);
        t[msc] := i;
        a[i+1] := a[i+1]-a[i];
        gata := false;
      end;
    end;
  until gata = true;

  gata := false;

  for i := n-1 downto 1 do
  begin
    if a[i] <> a[i+1] then begin gata := true; break; end;
    inc(msc);
    t[msc] := i;
  end;

  assign(fo,'mutari.out'); rewrite(fo);
  if gata = false then
  begin
  writeln(fo,msc);
  for i := 1 to msc do
    writeln(fo,t[i]);
  end
  else
    write(fo,'-1');

  close(fo);
end.
