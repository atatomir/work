var n,i,e1,e2,x,cx,t,ant,sum,rand,i1,i2,summax:longint;
    v:array[1..2,0..10001]of shortint;
    bufin:array[1..65000]of byte;
    iesi:boolean;

procedure afla;
begin
  v[1,e1+1] := 0; v[2,e2+1] := 0;  sum := 0; i1 := 0; i2 := 0;
  iesi := false;
  repeat
    if rand = 1 then
    begin
      inc(i1);
      while v[1,i1] >= ant do inc(i1);
      if v[1,i1] = 0 then
        iesi := true
      else
        sum := sum + v[1,i1];
      ant := v[1,i1];
    end
    else
    begin
      inc(i2);
      while v[2,i2] >= ant do inc(i2);
      if v[2,i2] = 0 then
        iesi := true
      else
        sum := sum + v[2,i2];
      ant := v[2,i2];
    end;
    if rand =1 then rand := 2 else rand := 1;
  until iesi = true;
end;

begin
  assign(input,'cuburi.in'); reset(input);
  assign(output,'cuburi.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); e1 := 0; e2 := 0;
  for i := 1 to n do
  begin
    readln(x,cx);
    if cx = 1 then
    begin
      inc(e1);
      v[1,e1] := x;
    end
    else
    begin
      inc(e2);
      v[2,e2] := x;
    end;
  end;

  repeat
    iesi := true;
    for i := 1 to e1-1 do
      if v[1,i] < v[1,i+1] then
      begin
        t := v[1,i];
        v[1,i] := v[1,i+1];
        v[1,i+1] := t;
        iesi := false;
      end;
  until iesi = true;
  repeat
    iesi := true;
    for i := 1 to e2-1 do
      if v[2,i] < v[2,i+1] then
      begin
        t := v[2,i];
        v[2,i] := v[2,i+1];
        v[2,i+1] := t;
        iesi := false;
      end;
  until iesi = true;

  if v[1,1] > v[2,1] then
  begin
    rand := 1;
    ant := v[1,1]+1;
  end
  else
  begin
    rand := 2;
    ant := v[2,1]+1;
  end;

  afla;
  summax := sum;
  if v[1,1] = v[2,1] then
  begin
    rand := 1;  ant := v[1,1]+1;
    afla;
    if summax < sum then summax := sum;
  end;


  writeln(summax);


  close(input);
  close(output);
end.
