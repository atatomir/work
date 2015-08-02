uses crt;
var chr:char;
    i:byte;


begin
clrscr;
i:= 1;

repeat
  if i = 1 then
  begin
    textcolor(red);
    writeln('rosu ');
    textcolor(white);
  end;

  if i = 2 then
  begin
    textcolor(blue);
    writeln('albastru ');
    textcolor(white);
  end;

  if i = 3 then
  begin
    textcolor(brown);
    writeln('verde ');
    textcolor(white);
  end;


chr := readkey;

case readkey of
  #75:dec(i);
  #77:inc(i);
end;






until chr = #13;

end.
