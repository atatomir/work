var n,i,op,lung,nn,h,hh,max,lmax,stopmax:longint;
    a:array[0..400005]of longint;
    r,lg:array[0..400005]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'buline.in'); reset(input);
  assign(output,'buline.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do
  begin
    readln(a[i],op);
    if op = 0 then a[i] := -a[i];
  end;

  for i := n+1 to 2*n do
  begin
    a[i] := a[i-n];
    r[i] := a[i]; r[i-n] := a[i];
  end;

  lung := 1; nn := 2*n-1; lg[1] := 1;
  for i := 2 to nn do
  begin
    h := r[i-1] + r[i]; inc(lung);
    if lung > n then
    begin
      hh := i-n;
      h := h - a[hh];
      lung := n;
      inc(hh);

      while (hh < i)and(a[hh] < 0) do
      begin
        h := h - a[hh];
        dec(lung);
        inc(hh);
      end;
    end;

    if h <= r[i] then
    begin
      lung := 1;
    end
    else
    begin
      r[i] := h;
    end;

    lg[i] := lung;
  end;

  max := -1;
  for i := 1 to nn do
  begin
    if max  < r[i] then
    begin
      max := r[i];
      lmax := lg[i];
      stopmax := i;
    end;
    //writeln(r[i]);
  end;

  h := stopmax-lmax;
  if h < 0 then h := n - h + 2 else inc(h);

  writeln(max,' ',h,' ',lmax);

  close(input);
  close(output);
end.
