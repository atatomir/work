var n,i,x,y,max,j,t:longint;
    ln:array[1..2,-1000..1000]of longint;
    d1,d2,dr:longint;
    zz:boolean;
    a:array[0..2001,1..2]of longint;
    ram,ant,r,h,h2:longint;

begin
  assign(input,'puncte6.in'); reset(input);
  assign(output,'puncte6.out'); rewrite(output);

  for i := -1000 to 1000 do
  begin
    ln[1,i] := 0;
    ln[2,i] := 0;
  end;
  d1 := 0; d2 := 0;  zz := false;

  readln(n);
  for i := 1 to n do
  begin
    readln(x,y);
    inc(ln[1,x]); inc(ln[2,y]);

    if x = y then
    begin
      inc(d1);
      if x = 0 then
      begin
        inc(d2);
        zz := true;
      end;
    end
    else
    if x = -y then
      inc(d2);

  end;

  max := 0;
  for i := - 1000 to 1000 do
  begin
    if ln[1,i] > max then max := ln[1,i];
    if ln[2,i] > max then max := ln[2,i];
  end;
  writeln(max);

  dr := 0;
  if d1 >= 2 then inc(dr);
  if d2 >= 2 then inc(dr);
  if zz then
  begin
    dec(d1);
    dec(d2);
  end;
  dr := dr + d1*d2;
  writeln(dr);

  t := 0; ram := 0;
  for j := -1000 to 1000 do
  begin
    if ln[1,j] > 0 then
    begin
      inc(t);
      a[t,1] := ln[1,j];
      a[t,2] := j;
      ram := ram + a[t,1];
    end;
  end;


  r := 0; ant := -1;
  while ram <> 0 do
  begin
    for i := 1 to t do
    begin
      if r >= a[i,1] then
      begin
        r := r - a[i,1];
      end
      else
      begin
        h := a[i,1] - r;
        h2 := h div 3; if h mod 3 > 0 then inc(h2);
        a[i,1] := a[i,1] - h2; ram := ram - h2;
        case h mod 3 of
          0: r := 0;
          1: r := 2;
          2: r := 1;
        end;
        ant := i;
      end;

    end;

  end;

  writeln(a[ant,2]);

  close(input);
  close(output);
end.
