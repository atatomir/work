var n,m,k,i,j,x1,x2:longint;
    a,ma:array[0..1001,0..1001]of byte;
    bufin:array[1..65000]of byte;
    max,imax:longint;

begin
  assign(input,'vecini.in'); reset(input);
  assign(output,'vecini.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m,k);  max := 0; imax := 0;
  for i := 1 to n do
    for j := 1 to m do
    begin
      a[i,j] := 0;
      ma[i,j] := 0;
    end;

  for i := 1 to k do
  begin
    readln(x1,x2); ma[x1,x2] := 1;
    if x1 > 1 then
    begin
      inc(a[x1-1,x2]);
      if x2 > 1 then inc(a[x1-1,x2-1]);
      if x2 < m then inc(a[x1-1,x2+1]);
    end;
    if x1 < n then
    begin
      inc(a[x1+1,x2]);
      if x2 > 1 then inc(a[x1+1,x2-1]);
      if x2 < m then inc(a[x1+1,x2+1]);
    end;
    if x2 > 1 then inc(a[x1,x2-1]);
    if x2 < m then inc(a[x1,x2+1]);
  end;

  for i := 1 to n do
    for j := 1 to m do
    begin
      if ma[i,j] = 1 then
      begin
        if a[i,j] > max then
        begin
          imax := 1;
          max := a[i,j];
        end
        else
          if a[i,j] = max then inc(imax);
      end
      else
      begin
        a[i,j] := 8-a[i,j];
        if i = 1 then a[i,j] := a[i,j] - 3;
        if j = 1 then a[i,j] := a[i,j] - 3;
        if (i=1) and (j=1) then inc(a[i,j]);
        if i = n then a[i,j] := a[i,j] - 3;
        if j = m then a[i,j] := a[i,j] - 3;
        if (i=n) and (j=m) then inc(a[i,j]);

        if a[i,j] > max then
        begin
          imax := 1;
          max := a[i,j];
        end
        else
          if a[i,j] = max then inc(imax);
      end;
    end;


  writeln(max,' ',imax);

  close(input);
  close(output);
end.