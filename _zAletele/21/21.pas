uses crt;
var a:array[1..14]of byte;
    i:byte;
    v:byte;
    x:byte;
    c:char;
    s:array[1..2]of byte;

procedure aleatoriu(y:byte);
begin
  repeat
    x:= random(v);
  until a[x]<=3 ;
  inc(a[x]);
  writeln('Continui? Daca da apasa Y , daca nu apasa N');
  c:=readkey;
  if c='y'then
  begin
    s[y]:=s[y]+x;
    writeln('Cartea: ',x,' Suma: ',s[y]);
    aleatoriu(y);
  end;
end;

begin
  v:=14;
  clrscr;
  randomize;
  for i := 1 to 14 do a[i]:=0;
  writeln('                        Jocul 21');
  delay(2000);
  writeln('                        Jucatorul nr 1');
  writeln('Suma actuala:0');
  s[1]:=0; s[2]:=0;
  aleatoriu(1);
  clrscr;
  Writeln('Suma la care v-ati oprit este: ',s[1]);
  clrscr;
  Writeln('Jucatorul 2 va incepe in 5 secunde!') ;
  delay(5000);
  clrscr;
  //for i := 1 to 14 do a[i]:=0;
  writeln('                    Jucatorul 2');
  writeln('Suma actuala: 0')                      ;
  aleatoriu(2);
  writeln('Suma la care v-ati oprit : ',s[2]);
  writeln('Sa aflam rezultatele ...');
  delay(3000);
  clrscr;
  writeln('Rezultate:')  ;
  Writeln('Jucatorul 1 a ajuns la : ' ,s[1]);
  writeln('Jucatorul 2 a ajuns la : ', s[2]);
  if (s[1]=21)and(s[2]=21) then  writeln('Toti jucatorii au castigat!');
  if (s[1]=21)and(s[2]<>21) then writeln('Jucatorul 1 a castigat');
  if (s[1]<>21)and(S[2]=21) then writeln('Jucatorul 2 a castigat');
  if (s[1]>21)and(s[2]>21) then writeln('Ambii jucatori au pierdut');
  if (s[1]<21)and(s[2]>21) then writeln('Jucatorul 1 a castigat');
  if (s[1]>21)and(s[2]<21) then writeln('Jucatorul 2 a castigat');
  if (s[1]<21)and(s[2]<21) then
    if 21-s[1]<21-s[2] then writeln('Jucatorul 1 a castigat')
    else
      if 21-s[1]>21-s[2] then writeln('Jucatorul 2 a castigat')
      else
        writeln('Ambii jucatori au castigat');



  delay(30000);



end.
