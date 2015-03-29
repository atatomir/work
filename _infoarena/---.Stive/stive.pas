var n,nn,cont,i,start,stop,m,ri,act,j:longint;
    bufout:array[1..65000]of byte;
    a:array[1..30005]of boolean;
    r:array[1..30000]of longint;

procedure add(x:longint);
begin
  inc(ri);
  r[ri] := x;
end;

begin
  assign(input,'stive.in'); reset(input);
  assign(output,'stive.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(n); nn := n;
  cont := 0;
  while nn <> 0 do
  begin
    inc(cont);
    nn := nn div 2;
  end;

  writeln(cont);

  for i := 1 to n do a[i] := true; start := 1 ; stop := n;

  for i := 1 to cont do
  begin
    m := (stop-start+1)div 2+1; ri := 0;
    act := 0;

    for j := 1 to n do
    begin
      if a[j] = false then
        act := 0
      else
        inc(act);
      if act = m then a[j] := false;
      if act >= m then add(j);
    end;

    stop := m-1;

    write(ri,' ');
    for j := 1 to ri do write(r[j],' ');

    writeln(m);
  end;






  close(input);
  close(output);
end.