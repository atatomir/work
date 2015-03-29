var n,m,i,h,ad,mint:longint;
    r,j:array[1..101,1..101]of longint;
    x:char;
    bufin:array[1..65000]of byte;
    gata:boolean;
    min,pos1m,pos2m:longint;

procedure rezolva_r(x,y,ad:longint);
begin
  if r[x,y] = ad then
  begin
    if (x > 1) and (r[x-1,y] = 0) then begin r[x-1,y] := ad+1; gata := false; end;
    if (x < n) and (r[x+1,y] = 0) then begin r[x+1,y] := ad+1; gata := false; end;
    if (y > 1) and (r[x,y-1] = 0) then begin r[x,y-1] := ad+1; gata := false; end;
    if (y < m) and (r[x,y+1] = 0) then begin r[x,y+1] := ad+1; gata := false; end;

    if (x > 1) and (y > 1) and (r[x-1,y-1] = 0) then begin r[x-1,y-1] := ad+1; gata := false; end;
    if (x < n) and (y > 1) and (r[x+1,y-1] = 0) then begin r[x+1,y-1] := ad+1; gata := false; end;
    if (x > 1) and (y < m) and (r[x-1,y+1] = 0) then begin r[x-1,y+1] := ad+1; gata := false; end;
    if (x < n) and (y < m) and (r[x+1,y+1] = 0) then begin r[x+1,y+1] := ad+1; gata := false; end;

  end;
end;

procedure rezolva_j(x,y,ad:longint);
begin
  if j[x,y] = ad then
  begin
    if (x > 1) and (j[x-1,y] = 0) then begin j[x-1,y] := ad+1; gata := false; end;
    if (x < n) and (j[x+1,y] = 0) then begin j[x+1,y] := ad+1; gata := false; end;
    if (y > 1) and (j[x,y-1] = 0) then begin j[x,y-1] := ad+1; gata := false; end;
    if (y < m) and (j[x,y+1] = 0) then begin j[x,y+1] := ad+1; gata := false; end;

    if (x > 1) and (y > 1) and (j[x-1,y-1] = 0) then begin j[x-1,y-1] := ad+1; gata := false; end;
    if (x < n) and (y > 1) and (j[x+1,y-1] = 0) then begin j[x+1,y-1] := ad+1; gata := false; end;
    if (x > 1) and (y < m) and (j[x-1,y+1] = 0) then begin j[x-1,y+1] := ad+1; gata := false; end;
    if (x < n) and (y < m) and (j[x+1,y+1] = 0) then begin j[x+1,y+1] := ad+1; gata := false; end;

  end;
end;

begin
  assign(input,'rj.in'); reset(input);
  assign(output,'rj.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);

  for i := 1 to n do
  begin
    for h := 1 to m do
    begin
      read(x);
      case x of
        'X':begin  r[i,h] := -1; j[i,h] := -1;  end;
        ' ':begin  r[i,h] := 0 ; j[i,h] :=  0;  end;
        'R':begin  r[i,h] := 1; j[i,h]:= 0;   end;
        'J':begin  r[i,h] := 0; j[i,h]:= 1;   end;
      end;
    end;
    readln();
  end;

  ad := 1;

  repeat
    gata := true;
    for i := 1 to n do
      for h := 1 to m do
      begin
        rezolva_r(i,h,ad);
        rezolva_j(i,h,ad);
      end;
    inc(ad);
  until gata = true;

  min := 999999999;

  for i := 1 to n do
  begin
    for h := 1 to m do
    begin

      if (r[i,h] = j[i,h]) and (r[i,h] < min) and (r[i,h] > 0) and(j[i,h] > 0) then         //metoda 1 fara intoarcere
      begin
        min := r[i,h];
        pos1m := i;
        pos2m := h;
      end;

    end;
  end;

  write(min,' ',pos1m,' ',pos2m);

  close(input);
  close(output);
end.