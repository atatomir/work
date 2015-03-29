var n,cont,curent,i:longint;
    a:array[1..1000001]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'elmaj.in'); reset(input);
  assign(output,'elmaj.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);

   cont := 0;

  for i := 1 to n do
  begin
    read(a[i]);

    if (cont = 0) then
    begin
      curent := a[i];
      inc(cont);
    end
    else
    begin
     if a[i] = curent then
        inc(cont)
      else
        dec(cont);
     end;
  end;

  if cont <= 0 then
    write('-1')
  else
  begin
    cont := 0;
    for i := 1 to n do
      if a[i] = curent then inc(cont);
    if cont < (n div 2)+1 then
      write('-1')
    else
      write(curent,' ',cont);
  end;

  close(input);
  close(output);
end.
