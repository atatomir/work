uses crt;

var i :byte;
    chr:char;

procedure culori;
begin
  gotoxy(25,12);
  cursoroff;
  //writeln(wherex,wherey);
  if i = 1 then textcolor(red);
    write('rosu ');
  textcolor(white);
  if i = 2 then textcolor(blue);
    write('albastru ');
  textcolor(white);
  if i = 3 then textcolor(yellow);
    write('galben ');
  textcolor(white);
  if i = 4 then textcolor(green);
    write('verde ');
  textcolor(white);

  chr := readkey;
  if chr = #27 then
    exit
  else
  begin
    clrscr;
    if chr = #0 then
    begin
      chr := readkey;
      if chr = #75 then
        if i = 1 then i := 4 else dec(i);
      if chr = #77 then
        if i = 4 then i := 1 else inc(i);
      culori;
    end;
  end;
end;

begin
clrscr;
i:= 1 ;
culori;


end.