var f,fo:text;
    n,i,ij,grupe,cuvinte:byte;
    chr:char;
    a:array[1..128] of integer;
    gasit : boolean;
    s:integer;

begin
  assign(f,'grad.in'); reset(f);
  assign(fo,'grad.out'); rewrite(fo);

  readln(f,n);

  i := 1;
  s:= 0;
  cuvinte:= 0;
  grupe:= 0;

  repeat
    read(f,chr);

    if (chr = ' ') and ( s > 0 ) then
    begin
      inc(cuvinte);
      gasit := false;

      for ij := 1 to grupe do
      begin
         if a[ij] = s then
         begin
           gasit := true;
           break;
         end;
      end;

      if gasit = false then
      begin
        inc(grupe);
        a[grupe] := s;
      end;

      s:= 0;
    end;

    if (i = n) then
    begin
      gasit := false;
      inc(cuvinte);
      s := s +( ord(chr) - $60);

      for ij := 1 to grupe do
      begin
        if s=a[ij] then
        begin
          gasit := true;
          break;
        end;
      end;
        if gasit = false then
        begin
          inc(grupe);
        end;
    end;

    if (chr <> ' ') and (i <> n) then
    begin
      s := s + (ord(chr)- $60);
    end;





















    inc(i);
  until i = n+1;


  writeln(fo,' -------');
  writeln(fo,cuvinte);
  writeln(fo,grupe);







  close(f);
  close(fo);
end.
