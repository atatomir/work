var n,m:longint;
    a:array[0..1005,0..1005]of char;
    l:array[0..1005,0..1005]of longint;
    s:array[1..26]of longint;
    c:char;
    ok:array[1..1000,1..1000]of boolean;
    cont:longint;
    bufin:array[1..65000]of byte;
i,j,i1,j1,i2,j2:longint;
op,sh:longint;
h:byte;
    
begin
  assign(input,'matrix.in'); reset(input);
  assign(output,'matrix.out'); rewrite(output);
  settextbuf(input,bufin);
    
  readln(n,m);
  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(c); 
      a[i,j] := c;
    end;
    readln();
  end;
    
  for i := 1 to 26 do s[i] := 0;
    
  for i := 1 to m do
  begin
    for j := 1 to m do
    begin
      read(c); op := ord(c) - $60;
      inc(s[op]);
    end;
    readln();
  end;
    
  for i := 0 to n+1 do
  begin
    l[0,i] := 0;
    l[n+1,i] := 0;
    l[i,0] := 0;
    l[i,n+1] := 0;
  end;
    
 
   
  i1 := n-m+1;
  j1 := i1;
  for i :=1 to i1 do
    for j :=1  to j1 do
      ok[i,j] := true;
  h := 0; 
  for c := 'a' to 'z' do
  begin
    h := h + 1;
    sh :=s[h]; 
    for i := 1 to n do
      for j := 1 to n do
        if a[i,j] = c then
          l[i,j] := l[i-1,j] + l[i,j-1] - l[i-1,j-1] + 1
        else
          l[i,j] := l[i-1,j] + l[i,j-1] - l[i-1,j-1] ;
    
    
    for i := 1 to i1 do begin
      i2 := i+m;
      for j := 1 to j1 do
      begin
        j2 := j+m; 
        if ok[i,j] then
          if sh <> l[i2-1,j2-1] - l[i-1,j2-1] - l[i2-1,j-1] + l[i-1,j-1] then
            ok[i,j] := false;
      end;
    end;
    
  end;
    
  cont := 0;
  for i := 1 to i1 do
  begin
    for j := 1 to j1 do
    begin
      if ok[i,j] then inc(cont);
    end;
  end;
    
  writeln(cont);
    
  close(input);
  close(output);
end.