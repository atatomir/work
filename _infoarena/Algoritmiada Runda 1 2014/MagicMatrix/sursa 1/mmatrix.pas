var t,ti,h:longint;
    n,i,j:longint;
    bufin:array[1..65000]of byte;
    v:array[0..501]of int64;
    x,s:int64;
    ok:boolean;

begin
  assign(input,'magicmatrix.in'); reset(input);
  assign(output,'magicmatrix.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    for i := 1 to n do
    begin
      for j := 1 to n do
      begin
        read(x);
        h := j-i+1;
        if j < i then h := n + h;
        v[h] := v[h] + x;
      end;
      readln();
    end;

    s := 0;
    for i := 1 to n do s := s + v[i];

    if s mod n <> 0 then
      writeln('NO')
    else
    begin
      s := s div n; ok := true;
      for i := 1 to n do
        if v[i] <> s then
        begin
          ok := false;
          break;
        end;
      if ok then writeln('YES') else writeln('NO');
    end;
  end;



  close(input);
  close(output);
end.