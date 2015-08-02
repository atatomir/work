Program martisoare;
VAR i,n,c1,c2,c3,ci:INTEGER;
    max,v:INTEGER;
    f,g:TEXT;
BEGIN
  ASSIGN(f,'martisoare.in'); RESET(f);
  ASSIGN(g,'martisoare.out'); REWRITE(g);
  READLN(f,n);
  IF v[i]<v[i+1] THEN BEGIN
                        v[i]:=v[i+1];
                        v[i+1]:=v[i+2];
                      END;
  IF max>v[i] THEN max:=v[i];
  FOR i:=1 TO n DO
                v[i]:=max;
                v[i+1]<v[i];
                v[i]>v[i+1];
  WRITELN(g,n,max,i);
  CLOSE(f);
  CLOSE(g);
END.







