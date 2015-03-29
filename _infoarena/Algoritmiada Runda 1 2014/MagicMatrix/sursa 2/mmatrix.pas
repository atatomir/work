var t,ti,x1,x2,h:longint;
    n,i,j:longint;
    bufin:array[1..65000]of byte;
    a:array[0..501,0..501]of longint;
    ok:boolean;

begin
  assign(input,'magicmatrix.in'); reset(input);
  assign(output,'magicmatrix.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n); ok := true;
    for j := 1 to n do read(a[1,j]); readln();
    for i := 2 to n do
    begin
      read(a[i,1]);
      for j := 2 to n do
      begin
        read(a[i,j]);
        x1 := a[i-1,j-1] + a[i,j];
        x2 := a[i-1,j] + a[i,j-1];
        if x1 <> x2 then
        begin
          ok := false;
          break;
        end;
      end;

      readln();  h := i;
      if not ok then break;
    end;

    if ok then
      writeln('YES')
    else
    begin
      writeln('NO');
      for i := h+1 to n do readln();
    end;
  end;



  close(input);
  close(output);
end.
