var n,p,k,i,j,x,y,max,cont,loc:longint;
    a:array[0..1001,0..1001]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'gradina.in'); reset(input);
  assign(output,'gradina.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,p,k);
  for i := 0 to n do
    for j := 0 to n do
      a[i,j] := 0;

  for i := 1 to p do
  begin
    readln(x,y);
    a[x,y] := 1;
  end;

  max := -1; cont := -1;

  for i := 1 to n do
    for j := 1 to n do
      a[i,j] := a[i-1,j] + a[i,j-1] + a[i,j] - a[i-1,j-1];

  for i := k to n do
    for j := k to n do
    begin
      loc := a[i,j] - a[i-k,j] - a[i,j-k] + a[i-k,j-k];
      if max < loc then
      begin
        max := loc;
        cont := 1;
      end
      else
      begin
        if max = loc then inc(cont);
      end;
    end;

  writeln(max);
  writeln(cont);

  close(input);
  close(Output);
end.
