var b,k,v:longint;
    nr:int64;
    c:char;

begin
  assign(input,'gsr.in'); reset(input);
  assign(output,'gsr.out'); rewrite(output);

  readln(b,k); nr := 0;

  while not eof(input) do
  begin
    read(c); if pos(c,'0123456789ABCDEF') = 0 then break;
    if ord(c) > $3A then
      case c of
        'A': v := 10;
        'B': v := 11;
        'C': v := 12;
        'D': v := 13;
        'E': v := 14;
        'F': v := 15;
      end
    else
      v := ord(c) - $30;

    nr := nr*b + v;
    nr := nr mod k;

  end;

  writeln(nr);

  close(input);
  close(output);
end.
