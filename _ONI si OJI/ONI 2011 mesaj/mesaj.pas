var ps:array[1..27]of char;
    p,n,i,t,j,e,min:longint;
    r:array[1..2010]of char;
    bufin,bufout:array[1..65000]of byte;
    rand:array[1..27]of integer;
    iesi:boolean;
    c,minc:char;
    apar:array[1..100]of longint;

begin
  assign(input,'mesaj.in'); reset(input);
  assign(output,'mesaj.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);


  readln(p);
  for i := 1 to p do read(ps[i]);
  readln();



  for i := 1 to p do rand[i] := i;
  for i := 65 to 90 do apar[i] := 0;

  repeat
    iesi := true;
    for i := 1 to p-1 do
    begin
      if ord(ps[i]) > ord(ps[i+1]) then
      begin
        c := ps[i];
        ps[i] := ps[i+1];
        ps[i+1] := c;
        t :=rand[i];
        rand[i] := rand[i+1];
        rand[i+1] := t;
        iesi := false;
      end;
    end;
  until iesi = true;


  readln(n);      //for i := 1 to p do write(rand[i]);

  for i := 1 to p do
  begin
    e := rand[i];
    for j := 1 to n div p do
    begin
      read(r[e]);
           t := ord(r[e]);
           inc(apar[t]);
      e := e + p;
    end;
    if n mod p >= rand[i] then
    begin
      read(r[e]);
           t := ord(r[e]);
           inc(apar[t]);
    end;
  end;

  min := 9999999; minc := '-';

  for i := 65 to 90 do
  begin
          //write(apar[i]);
    if (apar[i] < min) and(apar[i] <> 0 )  then
    begin
      minc := chr(i);
      min  := apar[i];
    end;
  end;

  writeln(minc);
  for i := 1 to n do write(r[i]);
  close(input);
  close(output);
end.
