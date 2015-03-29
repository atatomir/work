var s1,s2:array[1..100001]of char;
    l,i,l1,l2:longint;
    c1,c2:byte;
    a:array[97..122]of byte;
    iesi,prim:boolean;
    x:char;

begin
  assign(input,'ceas2.in'); reset(input);
  assign(output,'ceas2.out'); rewrite(output);

  prim := true;  l1 := 0;   l2 := 0;  x := 'a';

  while (ord(x) <> 13) and (ord(x) <> 10) do
  begin
    read(x);
    if pos(x,'abcdefghijklmnopqrstuvwxyz') > 0 then
    begin
      inc(l1);
      s1[l1] := x;
    end;
  end;

  while not eof(input) do
  begin
    read(x);
    if pos(x,'abcdefghijklmnopqrstuvwxyz') > 0 then
    begin
      inc(l2);
      s2[l2] := x;
    end;
  end;



  if l1 <> l2 then
    write('NU')
  else
  begin
    l := l1;
    iesi := false;
    for i := 97 to 122 do a[i] := 0;

    for i := 1 to l do
    begin
      c1 := ord(s1[i]);
      c2 := ord(s2[i]);
      if c1 <> c2 then
      begin
        if a[c1] = 0 then
          a[c1] := c2;
        if a[c1] <> c2 then
        begin
          iesi := true;
          break;
        end;
      end
      else
      begin
        if a[c1] <> 0 then
        begin
          iesi := true;
          break;
        end;
      end;
    end;

    if iesi = true then
      write('NU')
    else
    begin
      writeln('DA');
      for i := 97 to 122 do
      begin
        if a[i] <> 0 then
          writeln(char(i),' ',char(a[i]));
      end;
    end;

  end;

  close(input);
  close(Output);
end.
