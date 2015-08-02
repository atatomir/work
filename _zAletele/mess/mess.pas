uses crt;

var s,s2:string;
    f:text;
    i:word;
    c:char;
    scris:boolean;


begin
  clrscr;
  repeat
    scris := false;
    assign(f,'file.in'); reset(f);
    read(f,s);
    close(f);
    if s[1] = '@' then
    begin
      write('El/Ea: ');
      for i := 2 to length(s) do write(s[i]);
      writeln();
    end
    else
    if s[1] = '#' then
      begin
        write('Eu: ');
        readln(s2);
        rewrite(f);
        write(f,s,s2);
        close(f);
        scris := true;
      end;
    if scris = false then
    begin
      write('Eu: ');
      readln(s2);
      rewrite(f);
      write(f,'#');
      write(f,s2);
      close(f)

    end;

    c:= readkey;
  until c = #27;
  rewrite(f);
  close(f);
end.
