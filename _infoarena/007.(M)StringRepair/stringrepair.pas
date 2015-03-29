var fin,fo:text;
    i:longint;
    a:array[1..200000]of char;
    c:char;
    doi : Boolean;

begin
  assign(fin,'sr.in'); reset(fin);
  assign(fo,'sr.out'); rewrite(fo);

  doi := false;
  i := 0;
  while not eof(fin) do
  begin
    read(fin,c);
    if ord(c)  > 13 then
    begin
      if doi = false then begin i := i + 1 ; a[i] := c end
      else
      begin
        while a[i] <> c do inc(i);
        write(fo,i,' ');
        inc(i);
      end;
    end
    else
    begin
      doi := true;
      i := 1;
    end;

  end;

  close(fin); close(fo);
end.

