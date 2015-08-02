Program martisoare;
VAR n,i:BYTE;
    max:INTEGER;
    f,g:TEXT;
BEGIN
  ASSIGN(f,'martisoare.in'); RESET(f);
  ASSIGN(g,'martisoare.out'); REWRITE(g);
  READLN(f,g);
  FOR n:=4 TO i DO BEGIN
                 i:=n;
               END;
  CLOSE(f); CLOSE(g);
END.
