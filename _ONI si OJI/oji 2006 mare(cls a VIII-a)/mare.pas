var n,i,x,h,h2,j,l,max,maxi,maxj:longint;
    a:array[0..1000]of shortint;
    nr:array[0..1000]of smallint;
    t:array[0..10]of shortint;

procedure Expand(var i,j:longint);
begin
  while a[i-1] = a[j+1] do
  begin
    dec(i);
    inc(j);
  end;
end;

procedure Realocate(var i,j:longint);
begin
  while (nr[i-1]=nr[i]) or (nr[j]=nr[j+1]) do
  begin
    inc(i);
    dec(j);
    if i > j then
    begin
      i := j+1;
      break;
    end;
  end;
end;



begin
  assign(input,'mare.in'); reset(input);
  assign(output,'mare.out'); rewrite(output);

  readln(n);   h := 0;
  for i := 1 to n do
  begin
    read(x);  h2 := 0;
    while x <> 0 do
    begin
      inc(h2);
      t[h2] := x mod 10;
      x := x div 10;
    end;

    for j := h2 downto 1 do
    begin
      nr[h+j] := i;
      a[h+h2-j+1] := t[j];
    end;
    h := h + h2;
  end;

  a[0] := -5; nr[0] := -5;
  a[h+1] := -5; nr[h+1] := -5;
  max := -5; maxi := -5; maxj := -5;

  for l := 1 to h do
  begin
    i := l; j := l;
    Expand(i,j);
    if (nr[i-1] = nr[i]) or (nr[j] = nr[j+1]) then Realocate(i,j);
    if max < j-i+1 then
    begin
      max := j-i+1;
      maxi := i;
      maxj := j;
    end;

   if a[l] = a[l+1] then
   begin
     i := l; j := l+1;
     Expand(i,j);
     if (nr[i-1] = nr[i]) or (nr[j] = nr[j+1]) then Realocate(i,j);
     if max < j-i+1 then
     begin
       max := j-i+1;
       maxi := i;
       maxj := j;
     end;
   end;

  end;

  for i := maxi to maxj do write(a[i]);

  close(input);
  close(output);
end.
