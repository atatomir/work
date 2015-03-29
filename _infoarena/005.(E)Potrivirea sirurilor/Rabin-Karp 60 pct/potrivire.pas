program potrivire_metoda_Rabin_Karp;
const  mod1 = 100007;
       mod2 = 100021;
       baza = 73    ;

var a,b:ansistring;
    la,lb:longint;
    rez:array[1..1001]of longint;
    bufin,bufout:array[1..65000]of byte;
    i,l,i1,i2:longint;
    p1,p2:longint;
    hashA1,hashB1,hashA2,hashB2:longint;
    potriv:smallint;
    bi1,bi2:byte;

begin
  assign(input,'strmatch.in'); reset(input);
  assign(output,'strmatch.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(a);    la := length(a);
  readln(b);    lb := length(b);

  potriv := 0;

  if la < lb then
  begin
    p1 := 1; p2 := 1;
    hashA1 := 0; hashA2 := 0;  hashB1 :=0; hashB2 := 0;
    for i := 1 to la do
    begin
      hashA1 := ( hashA1 * baza + ord(a[i]) ) mod mod1 ;
      hashA2 := ( hashA2 * baza + ord(a[i]) ) mod mod2 ;
      hashB1 := ( hashB1 * baza + ord(b[i]) ) mod mod1;
      hashB2 := ( hashB2 * baza + ord(b[i]) ) mod mod2;
      if i > 1 then
      begin
        p1 := (p1 * baza) mod mod1;
        p2 := (p2 * baza) mod mod2;
      end;
    end;


    potriv := 0;

    if (hashA1 = hashB1) and (hashA2 = hashB2) then
    begin
      inc(potriv);
      rez[potriv] := 0;
    end;

    l := lb-la+1;

    for i := 2 to l do
    begin
      i1 := i - 1;
      i2 := i1 + la;
      bi1 := ord(b[i1]);
      bi2 := ord(b[i2]);
      hashB1 := ((hashB1 - ((bi1 * p1) mod mod1) + mod1) * baza + bi2) mod mod1;
      hashB2 := ((hashB2 - ((bi1 * p2) mod mod2) + mod2) * baza + bi2) mod mod2;

      if (hashA1 = hashB1) and (hashA2=hashB2) then
      begin
        inc(potriv);
        if potriv <= 1000 then
          rez[potriv] := i1 ;
      end;
    end;
  end
  else
  begin
    if la = lb then
    begin
      if a=b then begin
        potriv := 1;
        rez[1] := 0;
      end;
    end;
  end;

  writeln(potriv);
  if potriv >= 1000 then potriv := 1000;
  for i := 1 to potriv do
    write(rez[i] ,' ');

  close(input);
  close(output);
end.
