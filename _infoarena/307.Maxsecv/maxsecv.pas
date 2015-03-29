var bufin:array[1..65000]of byte;
    n:longint;
    max1,max2:longint;
    loc,i:longint;
    x:byte;

begin
  assign(input,'maxsecv.in'); reset(input);
  assign(output,'maxsecv.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); max1 := 0; max2 := 0;

  for i := 1 to n do
  begin
    read(x);
    if x = 1 then
      inc(loc)
    else
    begin
      if loc > max1 then
      begin
        max2 := max1;
        max1 := loc;
      end
      else
      if loc > max2 then
      begin
        max2 := loc;
      end;
      loc := 0;
    end;
  end;

      if loc > max1 then
      begin
        max2 := max1;
        max1 := loc;
      end
      else
      if loc > max2 then
      begin
        max2 := loc;
      end;


  write(max1+max2);

  close(input);
  close(output);
end.