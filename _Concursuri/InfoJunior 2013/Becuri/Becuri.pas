var n,i,j,k,curent,h,max,maxi,ic:longint;
    a:array[1..50005]of byte;

begin
  assign(input,'becuri.in'); reset(input);
  assign(output,'becuri.out'); rewrite(output);

  readln(n,k);  a[n+1] := 0;

  if k > 0 then
  begin

    curent := 0;

    for i := 1 to n do read(a[i]);

    i := 1; j := 1;
    for j := 1 to n do
    begin
      if a[j] = 0  then
      begin
        if curent < k then inc(curent) ;
        if curent = k then
        begin
          h := j;
          break;
        end;
      end;
    end;

    while a[h+1] = 1 do inc(h);
    j := h;

    max := j;  maxi := 1;

    while j < n do
    begin
      inc(j);
      while a[j+1] = 1 do inc(j);
      while a[i] = 1 do inc(i);
      inc(i);

      if max < j-i+1 then
      begin
        max := j-i+1;
        maxi := i;
      end;
    end;

    writeln(max,' ',maxi);

  end
  else
  begin

    max := 0;   curent := 0;  maxi := 0;  ic := 1;
    for i := 1 to n do
    begin
      read(a[1]);
      if a[1] = 1 then
        inc(curent)
      else
      begin
        if max < curent then
        begin
          max := curent;
          maxi := ic;
        end;
        curent := 0;
        ic := i + 1;
      end;
    end;

    if curent > max then
    begin
      max := curent;
      maxi := ic;
    end;
    write(max,' ',maxi);

  end;


  close(input);
  close(output);
end.
