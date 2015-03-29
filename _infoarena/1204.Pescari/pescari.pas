var n,m,i,j,p,x,cauta,g:longint;
    a:array[1..1001,1..1001]of longint;
    bufin,bufout:array[1..65000]of byte;
    iesi:boolean;

begin
  assign(input,'pescari.in'); reset(input);
  assign(output,'pescari.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n,m);
  for i := 1 to n do
  begin
    for j := 1 to m do
    begin
      read(x);
      if x = 2 then
        a[i,j] := 1
      else
        a[i,j] := 0;
    end;
    readln();
  end;

  cauta := 0;
  repeat
    inc(cauta);
    iesi := true;
    for i := 1 to n do
    begin
      for j := 1 to m do
      begin
        if a[i,j] = cauta then
        begin
          if (i > 1) and (a[i-1,j] = 0) then begin a[i-1,j] := cauta +1; iesi := false; end;
          if (j > 1) and (a[i,j-1] = 0) then begin a[i,j-1] := cauta +1; iesi := false; end;
          if (i < n) and (a[i+1,j] = 0) then begin a[i+1,j] := cauta +1; iesi := false; end;
          if (j < m) and (a[i,j+1] = 0) then begin a[i,j+1] := cauta +1; iesi := false; end;

          if (i > 1) and (j > 1) and (a[i-1,j-1] = 0) then begin a[i-1,j-1] := cauta +1; iesi := false; end;
          if (i < n) and (j > 1) and (a[i+1,j-1] = 0) then begin a[i+1,j-1] := cauta +1; iesi := false; end;
          if (i > 1) and (j < m) and (a[i-1,j+1] = 0) then begin a[i-1,j+1] := cauta +1; iesi := false; end;
          if (i < n) and (j < m) and (a[i+1,j+1] = 0) then begin a[i+1,j+1] := cauta +1; iesi := false; end;
        end;
      end;
    end;
  until iesi = true;

  close(input);
  assign(input,'pescari.in'); reset(input);
  settextbuf(input,bufin);

  readln(n,m,p);
  g := 0;


  for i := 1 to n do
  begin
    for j := 1 to m do
    begin
      read(x);
      if x = 1 then
      begin
        writeln(a[i,j]-1);
        inc(g);
        if g = p then break;
      end;
    end;
    readln();
  end;


  close(input);
  close(output);
end.