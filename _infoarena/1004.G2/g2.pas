var n,i,h:longint;
    doi,trei,cinci,sapte,mod2,mod3:integer;
    sase,patru,three,two:boolean;
begin
  assign(input,'g2.in'); reset(input);
  assign(output,'g2.out'); rewrite(output);

  read(n); doi := 0; trei := 0; cinci := 0; sapte := 0;

  while n mod 2 = 0 do
  begin
    inc(doi);
    n := n div 2;
  end;
  while n mod 3 = 0 do
  begin
    inc(trei);
    n := n div 3;
  end;
  while n mod 5 = 0 do
  begin
    inc(cinci);
    n := n div 5;
  end;
  while n mod 7 = 0 do
  begin
    inc(sapte);
    n := n div 7;
  end;
  if n = 1 then
  begin
    mod2 := doi mod 3;  doi := doi div 3;
    mod3 := trei mod 2; trei := trei div 2;
    patru := false; sase := false;  three := false; two := false;

    if (mod2>=1) and (mod3=1) then
    begin
      mod2 := mod2 - 1; mod3 := mod3 - 1;
      sase := true;
    end;
    if mod2 = 2 then
    begin
      patru := true;
      mod2 := 0;
    end;
    if mod2 = 1 then
    begin
      two := true;
    end;
    if mod3 = 1 then
    begin
      three := true;
    end;

    if two = true then write('2');
    if three = true then write('3');
    if patru = true then write('4');
    for i := 1 to cinci do write('5');
    if sase = true then write('6');
    for i := 1 to sapte do write('7');
    for i := 1 to doi do write('8');
    for i := 1 to trei do write('9');

  end
  else
    write('0');
  close(input);
  close(output);
end.
