var n,m,i,j,l:longint;
    cont:longint;
    r:array[0..405,0..405]of boolean;
    a:array[0..405,0..405]of smallint;
    iesi:boolean;
    bufin:array[1..65000]of byte;

begin
  assign(input,'simetric.in'); reset(input);
  assign(output,'simetric.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);

  for i := 1 to n do
  begin
    for j := 1 to m do
    begin
      read(a[i,j]);
      r[i,j] := true;
    end;
    readln();
  end;

  writeln(n*m);

  iesi := false; l := 1;
  repeat
    cont := 0; inc(l);

    for i := 1 to n-l+1 do
      for j := 1 to m-l+1 do
      begin
        if r[i,j] and r[i+1,j+1] and (a[i+l-1,j] = a[i,j+l-1]) then
          inc(cont)
        else
          r[i,j] := false;
      end;

    if cont = 0 then
      iesi := true
    else
      writeln(cont);
  until iesi;



  close(input);
  close(output);
end.