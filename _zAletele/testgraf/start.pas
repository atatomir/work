program testgraf;
uses crt;

var chr:char;
    s:string;


procedure scrie ;
begin
writeln('Cuvinte:');
writeln(' 1. este / 2. Mihai / 3 . nu / 4. atat / 5. inteligent / 6. de / 7 . ! ');
writeln('Apasa pe tastele 1,2,3..7 pentru a forma propozitia.');
writeln('Pentru a reseta apasa TAB.Apasa enter pentru a arata ca ai terminat !');
writeln('Propozitia ta este: ');
end;

procedure scrieprop (str:string);
begin
write(str);
s:= s + str;
end;


procedure repeated;
begin
repeat

  chr:= readkey;
  case chr of
    #49:scrieprop('este ');
    #50:scrieprop('Mihai ');
    #51:scrieprop('nu ');
    #52:scrieprop('atat ');
    #53:scrieprop('inteligent ');
    #54:scrieprop('de ');
    #55:scrieprop('!');
    #9:begin
         clrscr;
         scrie;
         s:='';
       end;
  end;


until chr = #13;

writeln();
  if s = 'Mihai nu este atat de inteligent !' then
  begin
    writeln('Bravo ai pus cuvintele in ordine');
    writeln('Daca doresti sa reiei jocul apasa TAB!');
    writeln('Apasa esc pentru a iesi sau enter pentru a relua jocul');
    chr:=readkey;
    case chr of
    #27:exit;
    #13:begin
          clrscr;
          scrie;
          s:='';
          repeated;
        end;
    end;
  end
  else
  begin
    writeln('Ai gresit ! Apasa Tab pentru a reincerca');
    repeated;
  end;
end;



begin
clrscr;
scrie;
repeated;
end.
