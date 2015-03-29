var i,j,n,x,cr,p:longint;
    l,c:array[1..100]of smallint;
    bufin:array[1..65000]of byte;
    x1,y1,x2,y2:longint;
    a:array[1..100,1..100]of byte;
  
begin
  assign(input,'magic2.in'); reset(input);
  assign(output,'magic2.out'); rewrite(output);
  settextbuf(input,bufin);
  
  readln(n);
  for i := 1 to n do
  begin
    l[i] := 0;
    c[i] := 0;
  end;
  
  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(x);  a[i,j] := x;
      l[i] := l[i] + x;
      c[j] := c[j] + x;
    end;
    readln();
  end;
  
  cr := l[1]; p := 1;
  
  for i := 2 to n do
  begin
    if p = 0 then
    begin
      cr := l[i];
    end;
    if cr = l[i] then
      inc(p)
    else
      dec(p);
  end;
  for i := 1 to n do
  begin
    if p = 0 then
    begin
      cr := c[i];
    end;
    if cr = c[i] then
      inc(p)
    else
      dec(p);
  end;
  
  x1 := 0; y1 := 0; x2 := 0; y2 := 0;
  
  for i := 1 to n do
    if l[i] <> cr then
    begin
      if x1 = 0 then x1 := i;
      x2 := i;
    end;
  for i := 1 to n do
    if c[i] <> cr then
    begin
      if y1 = 0 then y1 := i;
      y2 := i;
    end;
  
  
  if x1 = 0 then
    writeln('magic')
  else
  begin
    writeln('nu este magic');
  
    if x1 = x2 then
    begin
      writeln(x1,' ',y1,' ',x2,' ',y2);
      write(a[x1,y1] + cr -c[y1],' ');
      writeln(a[x2,y2] + cr -c[y1]);
    end
    else
    if y1 = y2 then
    begin
      writeln(x1,' ',y1,' ',x2,' ',y2);
      write(a[x1,y1] + cr - l[x1],' ');
      writeln(a[x2,y2] + cr - l[x2]);
    end
    else
    begin
        if l[x1] <> c[y1] then
      begin
        x := y1; y1 := y2 ; y2 := x;
      end;
      writeln(x1,' ',y1,' ',x2,' ',y2);
      write(a[x1,y1] + cr - l[x1],' ');
      writeln(a[x2,y2] + cr - l[x2]);
    end;
  
  
  end;
  
  close(input);
  close(output);
end.