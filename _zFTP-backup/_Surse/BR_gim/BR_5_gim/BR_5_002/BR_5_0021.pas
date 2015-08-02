Program martisoare;
VAR f,g:text;
    n,max,i,j:Integer;
    c:ARRAY[1..100000] OF Integer;
BEGIN
  ASSIGN(f,'martisoare.in');RESET(f);
  ASSIGN(g,'martisoare.out');REWRITE(g);
  READLN(f,n);
  FOR i:=1 TO n DO READ(f,c[i]);
  FOR i:=1 TO n-1 DO BEGIN
                     IF c[i]>c[i+1] THEN BEGIN
                                           IF c[i] DIV 10000>c[i+1] DIV 10000 THEN WRITE(g,c[i] DIV 10000,' ');
                                           IF c[i] DIV 1000>c[i+1] DIV 1000 THEN IF c[i] div 10000>0 then WRITE(g,c[i] mod 10000 div 1000,' ')
                                                                                                      else write(g,c[i] div 1000,' ');
                                           if c[i] div 100>c[i+1] div 100 then if c[i] div 11000>0 then write(g,c[i] mod 10000 mod 1000 div 100,' ')
                                                                                                    else if c[i] div 1000>=0 then write(g,c[i] mod 1000 div 100,' ')
                                                                                                                             else write(g,c[i] div 100,' ');
                                           if c[i] div 10>c[i+1] div 10 then if c[i] div 11100>0 then write(g,c[i] mod 10000 mod 1000 mod 100 div 10,' ')
                                                                        else if c[i] div 1100>0 then write(g,c[i] mod 1000 mod 100 div 10,' ')
                                                                                                 else if c[i] div 100>=0 then write(c[i] mod 100 div 10,' ')
                                                                                                                         else write(c[i] div 10,' ');
                                           if c[i] mod 10>c[i+1] mod 10 then write(g,c[i] mod 10,' ');

                                        end;
                     if (c[i]<c[i+1]) and (not(c[i+1]-c[i]=1)) then writeln(g,c[i+1] div 10,' ',c[i+1] mod 10);
                     END;
    IF c[n]-c[1]=n-1 then writeln(g,'0',' ','0');
  writeln(g);
  for i:=1 to n-1 do
    if c[i+1]<c[i] then c[i]:=c[i+1]-1;
  max:=c[i];
  for i:=2 to n-1 do
    if c[i]>max then max:=c[i];
  writeln(g,max);
  close(f);close(g);
end.
