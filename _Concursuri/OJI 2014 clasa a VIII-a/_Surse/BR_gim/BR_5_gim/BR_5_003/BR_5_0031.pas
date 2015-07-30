Program martisoare;
var i:Byte;
    v:ARRAY [1..100] OF BOOLEAN;
    f,g:TEXT;
BEGIN
  ASSIGN(f,'martisoare.in'); RESET(f);
  ASSIGN(f,'martisoare.out'); REWRITE(g);
  READ(f,);
  IF v[i]<v[i+1] THEN BEGIN
                         v[i]:=v[i+1]
                         v[i+1]:=v[i+2]
                 ELSE WRITELN(g,v[i]);
  CLOSE(f); CLOSE(g);
END.