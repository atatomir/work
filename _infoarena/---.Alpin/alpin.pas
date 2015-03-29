var a:array[0..1050,0..1050]of smallint;
    r:array[0..1050,0..1050]of longint;
    n,i,j,max,mi,mj:longint;
    bufin,bufout:array[1..65000]of byte;
    rez:array[0..1000050,1..2]of longint;

procedure Recurs(val,i,j:longint);
begin
  if val > r[i,j] then
  begin
    r[i,j] := val;
    if a[i,j-1] > a[i,j] then Recurs(val+1,i,j-1);
    if a[i,j+1] > a[i,j] then Recurs(val+1,i,j+1);
    if a[i-1,j] > a[i,j] then Recurs(val+1,i-1,j);
    if a[i+1,j] > a[i,j] then Recurs(val+1,i+1,j);
  end;


end;

begin
  assign(input,'alpin.in'); reset(input);
  assign(output,'alpin.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(a[i,j]);
      r[i,j] := 0;
    end;
    readln();
  end;

  for i := 0 to n+1 do
  begin
    a[0,i] := -1; a[n+1,i] := -1;
    a[i,0] := -1; a[i,n+1] := -1;
    r[0,i] := -1; r[n+1,i] := -1;
    r[i,0] := -1; r[i,n+1] := -1;
  end;

  for i := 1 to n do
    for j := 1 to n do
    begin
      if r[i,j] = 0 then
        Recurs(1,i,j);
    end;

  max := -1;
  for i := 1 to n do
    for j := 1 to n do
      if r[i,j] > max then
      begin
        max := r[i,j];
        mi := i; mj := j;
      end;

  writeln(max);

  rez[0,1] := 1; rez[1,1] := mi; rez[1,2] := mj; dec(max);

  while max > 0 do
  begin
    if r[mi-1,mj] = max then dec(mi) else
    if r[mi+1,mj] = max then inc(mi) else
    if r[mi,mj-1] = max then dec(mj) else
    if r[mi,mj+1] = max then inc(mj);
    dec(max);
    inc(rez[0,1]); rez[rez[0,1],1] := mi; rez[rez[0,1],2] := mj;
  end;

  for i := rez[0,1] downto 1 do
    writeln(rez[i,1],' ',rez[i,2]);




  close(input);
  close(output);
end.
